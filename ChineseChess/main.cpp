#include "client.h"
#include <QApplication>
#include <paintwidget.h>
#include <gamewindow.h>
#include <controlwidget.h>
#include <client.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Client w1, w2;
    //PaintWidget w;
    //Game *game = new Game();
    //GameWindow w1(game, RED);
    //GameWindow w2(game, BLACK);
    //ControlWidget w1;
    MainWindow w1, w2;
    w1.show();
    w2.show();

    return a.exec();
}
