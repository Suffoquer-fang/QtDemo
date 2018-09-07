#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = 0);
    ~ServerDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ServerDialog *ui;
public:
    QString ip;
    int port;
};

#endif // SERVERDIALOG_H
