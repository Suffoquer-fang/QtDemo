#include "client.h"
#include "ui_client.h"

#include <QDebug>
#include <QMessageBox>


Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    socket = nullptr;
    server = nullptr;



}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_clicked()
{
    server = new QTcpServer(this);

    server->listen(QHostAddress::Any, ui->lineEdit_2->text().toInt());

    connect(server, &QTcpServer::newConnection, this, &Client::initAsServer);

}

void Client::getMsg()
{
    QString tmp = QString(socket->readAll());
    //qDebug() << tmp;
    Game *game = gameWindow->getGame();
    if(tmp == "GIVEUP")
    {
        game->endGame();
        game->setWinner(gameWindow->getPlayerColor());
        gameWindow->newRound();
        return;
    }

    if(tmp == "AFAT")
    {
        if(QMessageBox::question(gameWindow, "询问信息", "对方请求和棋，是否同意？") == QMessageBox::Yes)
        {
            gameWindow->acceptTie();
            return;
        }
        return;
    }

    if(tmp == "ACPT")
    {
        game->endGame();
        game->setWinner(EMPTY);
        gameWindow->newRound();
        return;
    }

    int x1 = tmp.left(1).toInt();
    int y1 = tmp.left(2).toInt() - 10 * x1;
    int x2 = tmp.left(3).toInt() - 100 * x1 - 10 * y1;
    int y2 = tmp.toInt() - 1000 * x1 - 100 * y1 - 10 * x2;

    //qDebug() << x1 << y1 << x2 << y2;


    game->moveStone(game->map()->getStoneAtPoint(x1, y1), x2, y2);
    //gameWindow->controlWidget->newRound(game->currColor());
    gameWindow->newRound();
    gameWindow->update();

}

void Client::on_pushButton_2_clicked()
{
    socket = new QTcpSocket(this);
    QString ip = ui->lineEdit->text();
    quint16 port = ui->lineEdit_2->text().toInt();
    socket->connectToHost(QHostAddress(ip), port);

    connect(socket, &QTcpSocket::connected, this, &Client::initAsClient);
}

void Client::on_pushButton_3_clicked()
{
    if(socket != nullptr)
        socket->write(QString("2124").toUtf8());
}

void Client::initAsClient()
{
    gameWindow = new GameWindow(new Game, BLACK);
    connect(socket, &QTcpSocket::readyRead, this, &Client::getMsg);
    connect(gameWindow, SIGNAL(newMsgToSend(QString)), this, SLOT(sendMessage(QString)));
    gameWindow->show();
}

void Client::initAsServer()
{
    gameWindow = new GameWindow(new Game, RED);
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Client::getMsg);
    connect(gameWindow, SIGNAL(newMsgToSend(QString)), this, SLOT(sendMessage(QString)));
    gameWindow->show();
}

void Client::sendMessage(QString msg)
{
    if(socket != nullptr)
        socket->write(msg.toUtf8());
}
