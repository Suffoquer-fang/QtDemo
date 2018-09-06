#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <stone.h>

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

signals:
    void timeRunOut();

private:
    Ui::ControlWidget *ui;
    QTimer *m_timeCounter;

    int m_cntTime;
    int m_totTime_black;
    int m_totTime_red;

    StoneColor m_currColor;
};

#endif // CONTROLWIDGET_H
