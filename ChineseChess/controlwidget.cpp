#include "controlwidget.h"
#include "ui_controlwidget.h"

QString SecToTime(int n)
{
    if(n == 0)  return "00:00";
    QString ret = "";
    if(n / 60 < 10)
        ret += "0";
    ret += QString::number(n / 60) + ":";

    if(n % 60 < 10)
        ret += "0";

    ret += QString::number(n % 60);

    return ret;
}

ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    //m_cntTime = 10;
    m_totTime_red = m_totTime_black = 0;
    ui->setupUi(this);
    m_timeCounter = new QTimer(this);
    connect(m_timeCounter, &QTimer::timeout, this, &ControlWidget::timeCount);
    ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/IMG/giveup.png);}"
                                  "QPushButton:hover{border-image: url(:/IMG/giveup_hover.png);}"
                                  "QPushButton:pressed{border-image: url(:/IMG/giveup_pressed.png);}");



    ui->pushButton_2->setStyleSheet("QPushButton{border-image: url(:/IMG/tie.png);}"
                                    "QPushButton:hover{border-image: url(:/IMG/tie_hover.png);}"
                                    "QPushButton:pressed{border-image: url(:/IMG/tie_pressed.png);}");




    ui->pushButton_3->setStyleSheet("QPushButton{border-image: url(:/IMG/save.png);}"
                                    "QPushButton:hover{border-image: url(:/IMG/save_hover.png);}"
                                    "QPushButton:pressed{border-image: url(:/IMG/save_pressed.png);}");





    ui->pushButton_4->setStyleSheet("QPushButton{border-image: url(:/IMG/load.png);}"
                                    "QPushButton:hover{border-image: url(:/IMG/load_hover.png);}"
                                    "QPushButton:pressed{border-image: url(:/IMG/load_pressed.png);}");





    ui->pushButton_5->setStyleSheet("QPushButton{border-image: url(:/IMG/draw.png);}"
                                    "QPushButton:hover{border-image: url(:/IMG/draw_hover.png);}"
                                    "QPushButton:pressed{border-image: url(:/IMG/draw_pressed.png);}");



    m_currColor = RED;
    m_timeCounter->start(1000);
    ui->lcdNumber_2->display(SecToTime(m_totTime_red));
    ui->lcdNumber_4->display(SecToTime(m_totTime_black));
    ui->lcdNumber->display("03:00");
    ui->lcdNumber_3->disconnect("00:00");


    //ui->lcdNumber->setParent(ui->label);
    newRound(RED);

}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::newRound(StoneColor color)
{
    m_currColor = color;
    m_cntTime = 180;
    if(color == RED)
    {

        ui->lcdNumber_3->display("00:00");
    }else
    {
        ui->lcdNumber->display("00:00");
    }
}

void ControlWidget::timeCount()
{
    m_cntTime--;
    if(m_currColor == RED)
    {
        m_totTime_red++;
        ui->lcdNumber->display(SecToTime(m_cntTime));

    }
    else
    {
        m_totTime_black++;
        ui->lcdNumber_3->display(SecToTime(m_cntTime));

    }
    ui->lcdNumber_2->display(SecToTime(m_totTime_red));
    ui->lcdNumber_4->display(SecToTime(m_totTime_black));
    if(m_cntTime == 0)
    {
        m_timeCounter->stop();
        emit timeRunOut();
    }
}

