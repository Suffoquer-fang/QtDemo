#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{

    QDesktopWidget* pDesktopWidget = QApplication::desktop();

    screenRect = QApplication::desktop()->screenGeometry();

    pix = new QPixmap();
    pix->load(":/IMG/face.png");
    timer = new QTimer(this);
    createBallTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PaintWidget::updateAll);
    connect(createBallTimer, &QTimer::timeout, this, &PaintWidget::createBall);


    this->setFixedSize(screenRect.width(), screenRect.height());
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint|Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground, true);
    timer->start(50);

    createBallTimer->start(5000);
}

PaintWidget::~PaintWidget()
{

}

void PaintWidget::updateAll()
{
    for(int i = 0; i < ballPool.size(); ++i)
    {

        GameObject *ball = ballPool[i];
        ball->move(100);
        ball->activate();
        ball->bounce();
    }
    //qDebug() << ball.velocity().y();
    update();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    for(int i = 0; i < ballPool.size(); ++i)
    {
        painter.save();
        GameObject *ball = ballPool[i];
        painter.translate(ball->center());
        painter.rotate(ball->rotation());

        painter.drawPixmap(QPointF(-ball->radius(), -ball->radius()), pix->scaled(2 * ball->radius(), 2 * ball->radius()));

        painter.restore();
    }



}

void PaintWidget::createBall()
{
    GameObject *ball = new GameObject();
    ball->setBoundary(screenRect);
    ballPool.push_back(ball);



}
