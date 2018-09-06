#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <gamewindow.h>
#include <game.h>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();


    void initAsClient();
    void initAsServer();

private slots:
    void sendMessage(QString msg);
    void on_pushButton_clicked();

    void getMsg();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Client *ui;

    QTcpSocket *socket;
    QTcpServer *server;

    GameWindow *gameWindow;

};

#endif // CLIENT_H
