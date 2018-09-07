#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include <QAction>

#include <gamewindow.h>

#include <QFile>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initAsServer();
    void initAsClient();

    void getNewConnection();
    void socketConnected();

    void startGameAsServer();
    void startGameAsClient();

    void loadFile();

    void sendGameInfo();

    void File2Stone(QString tmp);

    void handleOperation(QString tmp);

    void connectionFailed();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;

    QAction *createRoom;
    QAction *joinRoom;

    GameWindow *gameWindow;
    Game *game;

    QString loadPath;

    QTimer *timer;



public slots:
    void sendMessage(QString msg);
    void getMessage();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_radioButton_clicked(bool checked);
    void on_radioButton_2_clicked(bool checked);
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
