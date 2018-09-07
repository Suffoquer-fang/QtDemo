#include "clientdialog.h"
#include "ui_clientdialog.h"

ClientDialog::ClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientDialog)
{
    ui->setupUi(this);
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::on_pushButton_clicked()
{
    ip = ui->lineEdit->text();
    port = ui->lineEdit_2->text().toInt();
    done(1);
}
