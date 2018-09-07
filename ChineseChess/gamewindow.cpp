#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QPushButton>
#include <QFrame>
#include <QSoundEffect>
#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

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
    controlWidget->newRound(game->currColor());

    paintWidget->setGeometry(0, 0, 750, 750);
    controlWidget->setGeometry(800, 70, 280, 740);

    this->setFixedSize(1150, 900);

    jiangjun_sound = new QMediaPlayer;
    jiangjun_sound->setMedia(QMediaContent(QUrl("qrc:/SOUND/Woman_jiangjun.mp3")));
    jiangjun_sound->setVolume(0);
    jiangjun_sound->play();

    go_sound = new QMediaPlayer;
    go_sound->setMedia(QMediaContent(QUrl("qrc:/SOUND/go.mp3")));

    win_sound = new QMediaPlayer;
    win_sound->setMedia(QMediaContent(QUrl("qrc:/SOUND/win.mp3")));

    lose_sound = new QMediaPlayer;
    lose_sound->setMedia(QMediaContent(QUrl("qrc:/SOUND/lose.mp3")));

    tie_sound = new QMediaPlayer;
    tie_sound->setMedia(QMediaContent(QUrl("qrc:/SOUND/heqi.mp3")));
    //go_sound->setVolume(0);
    //go_sound->play();

    connect(paintWidget, SIGNAL(stoneMoved(QString)), this, SIGNAL(newMsgToSend(QString)));
    connect(paintWidget, &PaintWidget::roundEnded, this, &GameWindow::newRound);
    connect(paintWidget, &PaintWidget::stoneMoved, this, &GameWindow::playSounds);




    connect(controlWidget, &ControlWidget::click_giveup, this, &GameWindow::giveup);
    connect(controlWidget, &ControlWidget::click_tie, this, &GameWindow::askForATie);
    connect(controlWidget, &ControlWidget::click_save, this, &GameWindow::save);
    connect(controlWidget, &ControlWidget::timeRunOut, this, &GameWindow::giveup);


}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::newRound()
{
    //
    if(game->isGameEnd())
    {
        controlWidget->endGame();
        QString winnerInfo;
        if(game->winnerColor() == playerColor)
        {
            winnerInfo = "YOU WIN!";
            win_sound->play();
        }
        else if(game->winnerColor() == EMPTY)
        {
            winnerInfo = "IT'S A TIE";
            tie_sound->play();
        }
        else
        {
            winnerInfo = "YOU LOSE!";
            lose_sound->play();
        }
        QMessageBox::information(this, "", QString("WE HAVE A WINNER\n") + winnerInfo);
        return;
    }


    //paintWidget->setPlayerColor(game->currColor());
    controlWidget->newRound(game->currColor());
}

void GameWindow::giveup()
{
    if(game->isGameEnd())   return;
    emit newMsgToSend("OGIVEUP\n");
    game->endGame();
    game->setWinner(playerColor == RED ? BLACK : RED);
    newRound();
}

void GameWindow::askForATie()
{
    if(game->isGameEnd())   return;
    emit newMsgToSend("OAFAT\n");
}

void GameWindow::acceptTie()
{
    if(game->isGameEnd())   return;
    emit newMsgToSend("OACPT\n");
    game->endGame();
    game->setWinner(EMPTY);
    this->newRound();
}

void GameWindow::save()
{
    QString savePath = QFileDialog::getSaveFileName(this, "Save", "", tr("Text File(.txt)"));
    if(savePath.isEmpty())  return;
    if(QFileInfo(savePath).suffix().isEmpty())
        savePath.append(".txt");
    QFile file(savePath);
    if(!file.open(QIODevice::WriteOnly))    return;
    QTextStream stream(&file);

    stream << (game->currColor() == RED ? "red" : "black") << "\r\n";

    stream << stone2File(STONE_JIANG, game->currColor()) << "\r\n";
    stream << stone2File(STONE_SHI, game->currColor()) << "\r\n";
    stream << stone2File(STONE_XIANG, game->currColor()) << "\r\n";
    stream << stone2File(STONE_MA, game->currColor()) << "\r\n";
    stream << stone2File(STONE_JU, game->currColor()) << "\r\n";
    stream << stone2File(STONE_PAO, game->currColor()) << "\r\n";
    stream << stone2File(STONE_BING, game->currColor()) << "\r\n";

    StoneColor otherColor = game->currColor() == RED ? BLACK : RED;
    stream << (otherColor == RED ? "red" : "black") << "\r\n";

    stream << stone2File(STONE_JIANG, otherColor) << "\r\n";
    stream << stone2File(STONE_SHI, otherColor) << "\r\n";
    stream << stone2File(STONE_XIANG, otherColor) << "\r\n";
    stream << stone2File(STONE_MA, otherColor) << "\r\n";
    stream << stone2File(STONE_JU, otherColor) << "\r\n";
    stream << stone2File(STONE_PAO, otherColor) << "\r\n";
    stream << stone2File(STONE_BING, otherColor) << "\r\n";

}

void GameWindow::playSounds()
{
    if(game->isGameEnd())   return;

    go_sound->setVolume(100);
    go_sound->play();
    if(game->map()->is_JIANGJUN(RED) || game->map()->is_JIANGJUN(BLACK))
    {
        jiangjun_sound->setVolume(100);
        qDebug() << "jiangjun";
        jiangjun_sound->play();
    }
}

QString GameWindow::stone2File(StoneType type, StoneColor color)
{
    int cnt = 0;
    QString ret = "";

    for(int i = 0; i < game->map()->ally(color).size(); ++i)
    {
        if(game->map()->ally(color).at(i)->type() == type)
        {
            cnt++;
            StoneClass *tmp = game->map()->ally(color).at(i);
            ret += " <" + QString::number(8 - tmp->y()) + "," + QString::number(tmp->x()) + ">";
        }
    }

    ret.push_front(QString::number(cnt));

    return ret;
}
