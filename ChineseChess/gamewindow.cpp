#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QPushButton>
#include <QFrame>
#include <QSoundEffect>
#include <QDebug>

#include <QMessageBox>

GameWindow::GameWindow(Game *game, StoneColor color, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->game = game;
    if(game == nullptr)
        this->game = new Game();

    playerColor = color;


    paintWidget = new PaintWidget(this);
    paintWidget->setGame(this->game);
    paintWidget->setPlayerColor(playerColor);

    controlWidget = new ControlWidget(this);

    paintWidget->setGeometry(0, 0, 750, 750);
    controlWidget->setGeometry(800, 70, 280, 740);

    this->setFixedSize(1150, 900);

    connect(paintWidget, SIGNAL(stoneMoved(QString)), this, SIGNAL(newMsgToSend(QString)));
    connect(paintWidget, &PaintWidget::roundEnded, this, &GameWindow::newRound);
    //connect(paintWidget, &PaintWidget::stoneMoved, this, &GameWindow::doChecks);


    jiangjun_sound = new QMediaPlayer;
    jiangjun_sound->setMedia(QMediaContent(QUrl("qrc:/SOUND/Woman_jiangjun.mp3")));
    jiangjun_sound->setVolume(0);
    jiangjun_sound->play();

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::newRound()
{
    //
    if(game->map()->getWinner() != EMPTY)
    {
        QMessageBox::information(this, "", "WE HAVE A WINNER");
        return;
    }

    if(game->map()->is_JIANGJUN(RED) || game->map()->is_JIANGJUN(BLACK))
    {
        jiangjun_sound->setVolume(100);
        qDebug() << "jiangjun";
        jiangjun_sound->play();
    }
    //paintWidget->setPlayerColor(game->currColor());
    controlWidget->newRound(game->currColor());
}
