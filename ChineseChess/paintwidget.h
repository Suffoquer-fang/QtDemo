#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>

#include <mapclass.h>
#include <game.h>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *ev);

    void drawStone(QPainter* painter, StoneClass *stone);

    void drawMoveArea(QPainter* painter, QVector<QPoint> &area);

    void drawFocusRect(QPainter* painter, int x, int y);

    QPoint getClickPoint(int x, int y);

    void initPixMap();

    void setGame(Game *game) {m_game = game; m_map = game->map();}
    void setPlayerColor(StoneColor color) {m_playerColor = color;}

protected:
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
     void stoneMoved(QString moveinfo);
     void roundEnded();
public slots:


private:
    QPixmap *board;
    QPixmap *red_JIANG, *red_SHI, *red_XIANG, *red_MA, *red_JU, *red_PAO, *red_BING;
    QPixmap *black_JIANG, *black_SHI, *black_XIANG, *black_MA, *black_JU, *black_PAO, *black_BING;


    MapClass *m_map;
    Game *m_game;
    StoneColor m_playerColor;

    QTimer *m_focusTimer;

    QPainter *painter;

};

#endif // PAINTWIDGET_H
