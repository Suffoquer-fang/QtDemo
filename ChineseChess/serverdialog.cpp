#include "serverdialog.h"
#include "ui_serverdialog.h"

ServerDialog::ServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    port = 0;
}

ServerDialog::~ServerDialog()
{
    delete ui;
}

void ServerDialog::on_pushButton_clicked()
{
    ip = ui->lineEdit->text();
    port = ui->lineEdit_2->text().toInt();
    done(1);
}
