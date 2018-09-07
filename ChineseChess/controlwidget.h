#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <stone.h>
#include <game.h>

namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

    void newRound(StoneColor color);
    void timeCount();
    void endGame();

signals:
    void timeRunOut();
    void click_giveup();
    void click_save();
    void click_load();
    void click_tie();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ControlWidget *ui;
    QTimer *m_timeCounter;

    int m_cntTime;
    int m_totTime_black;
    int m_totTime_red;

    StoneColor m_currColor;
};

#endif // CONTROLWIDGET_H
