#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <Qpainter>
#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include <QTransform>
#include <QDesktopWidget>
#include <QApplication>

#include <vector>


#include <gameobject.h>

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    void createBall();
    void deleteBall(GameObject *ball);

public slots:
    void updateAll();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimer *timer;

    std::vector<GameObject*> ballPool;

    QPixmap *pix;

    QRect screenRect;

    QTimer *createBallTimer;
};

#endif // PAINTWIDGET_H
