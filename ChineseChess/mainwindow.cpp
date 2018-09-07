#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <serverdialog.h>
#include <clientdialog.h>
#include <QFileDialog>
#include <QFile>
#include <QChar>
#include <QDebug>
#include <QMenu>
#include <QMessageBox>

int CharToInt(QChar a)
{
    QString tmp(a);
    return tmp.toInt();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = nullptr;
    socket = nullptr;
    game = new Game();

    ui->groupBox_2->setEnabled(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton->setVisible(false);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &MainWindow::connectionFailed);

    createRoom = new QAction("create", this);
    joinRoom = new QAction("join", this);

    QMenu *tmp = this->menuBar()->addMenu("Option");
    tmp->addAction(createRoom);
    tmp->addAction(joinRoom);




    connect(createRoom, &QAction::triggered, this, &MainWindow::initAsServer);
    connect(joinRoom, &QAction::triggered, this, &MainWindow::initAsClient);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAsServer()
{
    ServerDialog *tmp = new ServerDialog(this);

    if(tmp->exec() == 1)
    {
        server = new QTcpServer(this);
        server->listen(QHostAddress::Any, tmp->port);
        connect(server, &QTcpServer::newConnection, this, &MainWindow::getNewConnection);
    }
    ui->groupBox_2->setEnabled(true);
     ui->pushButton_2->setText("断开等待");
    ui->label->setText("IP: " + tmp->ip);
    ui->label_2->setText("PORT: " + QString::number(tmp->port));
    ui->label_3->setText("等待中...");
    ui->pushButton_2->setVisible(true);
}

void MainWindow::initAsClient()
{
    ClientDialog *tmp = new ClientDialog(this);
    if(tmp->exec() == 1)
    {
       socket = new QTcpSocket(this);
       socket->connectToHost(QHostAddress(tmp->ip), tmp->port);
       connect(socket, &QTcpSocket::connected, this, &MainWindow::socketConnected);
    }

    ui->groupBox_2->setEnabled(true);
    ui->label->setText("IP: " + tmp->ip);
    ui->label_2->setText("PORT: " + QString::number(tmp->port));
    ui->label_3->setText("连接中");
    timer->start(5000);

    ui->pushButton_3->setEnabled(false);

}

void MainWindow::getNewConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::getMessage);
    ui->label_3->setText("连接成功");
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setEnabled(true);

    //startGameAsServer();
}

void MainWindow::socketConnected()
{
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::getMessage);
    ui->label_3->setText("连接成功");
    timer->stop();
    //startGameAsClient();


}

void MainWindow::sendMessage(QString msg)
{
    if(socket != nullptr)
        socket->write(msg.toUtf8());
}

void MainWindow::startGameAsServer()
{
    if(ui->radioButton->isChecked())
    {
        game = new Game();
        sendMessage("NewGame\n");
    }
    else
    {
        loadFile();
        sendMessage(QString("LoadGame\n") + (game->currColor() == RED ? "red\n" : "black\n"));
        //qDebug() << "load";
        sendGameInfo();
    }

    gameWindow = new GameWindow(game, RED);
    connect(gameWindow, SIGNAL(newMsgToSend(QString)), this, SLOT(sendMessage(QString)));

    gameWindow->show();

}

void MainWindow::startGameAsClient()
{
    gameWindow = new GameWindow(game, BLACK);
    connect(gameWindow, SIGNAL(newMsgToSend(QString)), this, SLOT(sendMessage(QString)));

    gameWindow->show();

}

void MainWindow::loadFile()
{
    game = new Game();
    MapClass *tmpmap = new MapClass;

    tmpmap->clear();

    if(loadPath.isEmpty())
        loadPath = QFileDialog::getOpenFileName(this, "open", ".");
    if(loadPath.isEmpty())  return;
    QFile file(loadPath);
    if(!file.open(QIODevice::ReadOnly)) return;

        QTextStream stream(&file);
        StoneColor color = (stream.readLine() == "red" ? RED : BLACK);
        for(int i = 0; i < 7; ++i)
        {
            QString line = stream.readLine();
            if(line.at(0) == "0")   continue;
            for(int j = 0; j < CharToInt(line.at(0)); ++j)
            {
                StoneClass *stone = new StoneClass(i + 1, color);
                stone->setPos(CharToInt(line.at(5 + 6 * j)), 8 - CharToInt(line.at(3 + 6 * j)));
                if(color == RED)
                    tmpmap->addRedStone(stone);
                else
                    tmpmap->addBlackStone(stone);
            }

        }

        StoneColor othercolor = (stream.readLine() == "red" ? RED : BLACK);
        for(int i = 0; i < 7; ++i)
        {
            QString line = stream.readLine();
            if(line.at(0) == "0")   continue;
            for(int j = 0; j < CharToInt(line.at(0)); ++j)
            {
                StoneClass *stone = new StoneClass(i + 1, othercolor);
                stone->setPos(CharToInt(line.at(5 + 6 * j)), 8 - CharToInt(line.at(3 + 6 * j)));
                if(othercolor == RED)
                    tmpmap->addRedStone(stone);
                else
                    tmpmap->addBlackStone(stone);
            }

        }



    game->startLoadedGame(tmpmap, color);
}

void MainWindow::sendGameInfo()
{
    for(int i = 0; i < game->map()->red().size(); ++i)
    {
        QString tmp = "R";
        tmp += QString::number(game->map()->red().at(i)->id());
        tmp += QString::number(game->map()->red().at(i)->x());
        tmp += QString::number(game->map()->red().at(i)->y());
        tmp += "\r\n";
        sendMessage(tmp);
    }

    for(int i = 0; i < game->map()->black().size(); ++i)
    {
        QString tmp = "B";
        tmp += QString::number(game->map()->black().at(i)->id());
        tmp += QString::number(game->map()->black().at(i)->x());
        tmp += QString::number(game->map()->black().at(i)->y());
        tmp += "\r\n";
        sendMessage(tmp);
    }

    sendMessage("END\n");



}

void MainWindow::getMessage()
{
    while(!socket->atEnd())
    {
        QString tmp = socket->readLine();
        qDebug() << tmp;
        if(tmp == "NewGame\n")
        {
            game = new Game();
            startGameAsClient();
            return;
        }
        if(tmp == "LoadGame\n")
        {
            game = new Game();
            game->map()->clear();
            if(socket->readLine() == "black\n")
                game->setCurrColor(BLACK);
            //return;
        }
        if(tmp.at(0) == "R")
        {
            tmp = tmp.remove(0, 1);
            StoneClass *stone = new StoneClass(tmp.left(1).toInt(), RED);
            tmp = tmp.remove(0, 1);
            stone->setPos(tmp.left(1).toInt(), tmp.left(2).toInt() % 10);
            game->map()->addRedStone(stone);
            //return;
        }
        if(tmp.at(0) == "B")
        {
            tmp = tmp.remove(0, 1);
            StoneClass *stone = new StoneClass(tmp.left(1).toInt(), BLACK);
            tmp = tmp.remove(0, 1);
            stone->setPos(tmp.left(1).toInt(), tmp.left(2).toInt() % 10);
            game->map()->addBlackStone(stone);
            //return;
        }
        if(tmp == "END\n")
        {
            startGameAsClient();
        }

        if(tmp.at(0) == "M")
        {
            int x1 = CharToInt(tmp.at(1));
            int y1 = CharToInt(tmp.at(2));
            int x2 = CharToInt(tmp.at(3));
            int y2 = CharToInt(tmp.at(4));
            game->moveStone(game->map()->getStoneAtPoint(x1, y1), x2, y2);
            gameWindow->newRound();
            gameWindow->update();
        }

        if(tmp.at(0) == "O")
        {
            handleOperation(tmp);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    loadPath = QFileDialog::getOpenFileName(this, "open", ".");
    //startGameAsServer();
}

void MainWindow::handleOperation(QString tmp)
{
    if(tmp == "OGIVEUP\n")
    {
        game->endGame();
        game->setWinner(gameWindow->getPlayerColor());
        gameWindow->newRound();
        return;
    }

    if(tmp == "OAFAT\n")
    {
        if(QMessageBox::question(gameWindow, "询问信息", "对方请求和棋，是否同意？") == QMessageBox::Yes)
        {
            gameWindow->acceptTie();
            return;
        }else
        {
            sendMessage("ORFST\n");
        }
        return;
    }

    if(tmp == "OACPT\n")
    {
        game->endGame();
        game->setWinner(EMPTY);
        gameWindow->newRound();
        return;
    }

    if(tmp == "ORFST\n")
    {
        //
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //game = new Game();
    startGameAsServer();
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    ui->pushButton->setVisible(!checked);
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    ui->pushButton->setVisible(checked);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text() == "断开等待")
    {
        //disconnect(server, &QTcpServer::newConnection, this, &MainWindow::getNewConnection);
        delete server;
        ui->label_3->setText("取消等待");
        ui->pushButton_2->setText("重新连接");
    }else
    {
        initAsServer();
        //connect(server, &QTcpServer::newConnection, this, &MainWindow::getNewConnection);
        ui->pushButton_2->setText("断开等待");
    }
}

void MainWindow::connectionFailed()
{
    ui->label_3->setText("连接失败");
    timer->stop();
}
