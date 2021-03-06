#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <game.h>
#include <paintwidget.h>
#include <QHBoxLayout>
#include <QWidget>
#include <controlwidget.h>

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaContent>
#include <QUrl>

#include <QCloseEvent>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(Game *game = nullptr, StoneColor color = RED, QWidget *parent = nullptr);
    ~GameWindow();

    void setPlayerColor(StoneColor color) {playerColor = color;}

    Game* getGame() {return game;}
    StoneColor getPlayerColor() {return playerColor;}

    void newRound();
    void playSounds();

    void closeEvent(QCloseEvent *ev);


signals:
    void newMsgToSend(QString msg);

public slots:
    void giveup();
    void askForATie();
    void acceptTie();
    void save();
    void timeOut();


private:
    Ui::GameWindow *ui;

    Game *game;
    StoneColor playerColor;

    QMediaPlayer *jiangjun_sound;
    QMediaPlayer *go_sound;
    QMediaPlayer *win_sound, *lose_sound, *tie_sound;


    QString stone2File(StoneType type, StoneColor color);

public:

    PaintWidget *paintWidget;
    ControlWidget *controlWidget;


};

#endif // GAMEWINDOW_H
