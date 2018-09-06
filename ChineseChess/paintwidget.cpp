#include "paintwidget.h"
#include <QPixmap>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    initPixMap();
    this->setFixedSize(board->size().width() + 100, board->size().height() + 100);

    m_map = nullptr;
    m_focusTimer = new QTimer(this);
    connect(m_focusTimer, &QTimer::timeout, [this]{m_map->focusStone()->reverse(); update();});
}

void PaintWidget::initPixMap()
{
    board = new QPixmap(":/IMG/Board.jpg");
    board = new QPixmap(board->scaled(board->size().width() * 0.8, board->size().height() * 0.8, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    red_PAO = new QPixmap(QPixmap(":/IMG/red_PAO.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    red_JIANG = new QPixmap(QPixmap(":/IMG/red_JIANG.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    red_SHI = new QPixmap(QPixmap(":/IMG/red_SHI.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    red_XIANG = new QPixmap(QPixmap(":/IMG/red_XIANG.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    red_MA = new QPixmap(QPixmap(":/IMG/red_MA.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    red_JU = new QPixmap(QPixmap(":/IMG/red_JU.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    red_BING = new QPixmap(QPixmap(":/IMG/red_BING.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    black_PAO = new QPixmap(QPixmap(":/IMG/black_PAO.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    black_JIANG = new QPixmap(QPixmap(":/IMG/black_JIANG.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    black_SHI = new QPixmap(QPixmap(":/IMG/black_SHI.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    black_XIANG = new QPixmap(QPixmap(":/IMG/black_XIANG.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    black_MA = new QPixmap(QPixmap(":/IMG/black_MA.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    black_JU = new QPixmap(QPixmap(":/IMG/black_JU.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    black_BING = new QPixmap(QPixmap(":/IMG/black_BING.png").scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}


void PaintWidget::paintEvent(QPaintEvent *ev)
{
    painter = new QPainter(this);


    if(m_map == nullptr)
    {
        // 处理
        return;
    }


    if(m_playerColor == RED)
    {
        painter->translate(board->width() + 100, board->height() + 100);
        painter->rotate(180);
    }

    painter->drawPixmap(50, 50, *board);

    for(int i = 0; i < m_map->red().size(); ++i)
    {
        drawStone(painter, m_map->red().at(i));
    }
    for(int i = 0; i < m_map->black().size(); ++i)
    {
        drawStone(painter, m_map->black().at(i));
    }

    if(m_map->focusStone() != nullptr)
    {
        QVector<QPoint> area;
        m_map->GetMoveArea(m_map->focusStone(), area);
        drawMoveArea(painter, area);

        drawFocusRect(painter, m_map->focusStone()->x(), m_map->focusStone()->y());
        //drawFocusRect(painter, old_x, old_y);
    }

    drawFocusRect(painter, m_map->recentMove()->old_x(), m_map->recentMove()->old_y());
    drawFocusRect(painter, m_map->recentMove()->new_x(), m_map->recentMove()->new_y());
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m_game->currColor() != m_playerColor) return;

    qDebug() << ev->x() << ev->y();
    QPoint clickpos = getClickPoint(ev->x(), ev->y());
    int x = clickpos.x();
    int y = clickpos.y();

    m_map->recentMove()->set(-1, -1, -1, -1);
    if(m_map->getColorAtPoint(x, y) == m_playerColor)
    {
        m_map->setFocusStone(m_map->getStoneAtPoint(x, y));

        m_map->focusStone()->select();
        m_focusTimer->start(500);
    }
    else
    {
        if(m_map->focusStone() != nullptr)
        {
            m_focusTimer->stop();

            if(m_game->moveStone(m_map->focusStone(), x, y))
            {

                emit stoneMoved(QString::number(m_map->recentMove()->old_x()) + QString::number(m_map->recentMove()->old_y()) + QString::number(x) + QString::number(y));
                emit roundEnded();
            }
        }
    }





    update();
}

void PaintWidget::drawStone(QPainter *painter, StoneClass *stone)
{
    int ty = stone->x() * delta_x - radius + offset;
    int tx = stone->y() * delta_y - radius + offset;
    QPixmap *tmp;
    switch (stone->type()) {
    case STONE_JIANG:
        tmp = (stone->color() == RED) ? red_JIANG : black_JIANG;
        break;
    case STONE_SHI:
        tmp = (stone->color() == RED) ? red_SHI : black_SHI;
        break;
    case STONE_XIANG:
        tmp = (stone->color() == RED) ? red_XIANG : black_XIANG;
        break;
    case STONE_MA:
        tmp = (stone->color() == RED) ? red_MA : black_MA;
        break;
    case STONE_JU:
        tmp = (stone->color() == RED) ? red_JU : black_JU;
        break;
    case STONE_PAO:
        tmp = (stone->color() == RED) ? red_PAO : black_PAO;
        break;
    case STONE_BING:
        tmp = (stone->color() == RED) ? red_BING : black_BING;
        break;
    default:
        break;
    }
    painter->save();


    painter->translate(tx, ty);

    if(m_playerColor == RED)
    {
        painter->translate(2 * radius, 2 * radius);
        painter->rotate(180);
    }

    if(stone != m_map->focusStone() || stone->isSelected())
        painter->drawPixmap(QPoint(0, 0), *tmp);

    painter->restore();


}

void PaintWidget::drawMoveArea(QPainter *painter, QVector<QPoint> &area)
{
    for(int i = 0; i < area.size(); ++i)
    {
        int ty = area[i].x() * delta_x + offset;
        int tx = area[i].y() * delta_y + offset;
        painter->drawEllipse(QPoint(tx, ty), 30, 30);
    }
}

void PaintWidget::drawFocusRect(QPainter *painter, int x, int y)
{
    if(x == -1 || y == -1)  return;
    int ty = x * delta_x + offset;
    int tx = y * delta_y + offset;
    painter->save();
    painter->translate(tx, ty);
    painter->setPen(Qt::red);
    painter->drawLine(-radius, -radius, -radius, -radius + 15);
    painter->drawLine(-radius, -radius, -radius + 15, -radius);

    painter->drawLine(-radius, radius, -radius, radius - 15);
    painter->drawLine(-radius, radius, -radius + 15, radius);

    painter->drawLine(radius, -radius, radius, -radius + 15);
    painter->drawLine(radius, -radius, radius - 15, -radius);

    painter->drawLine(radius, radius, radius, radius - 15);
    painter->drawLine(radius, radius, radius - 15, radius);

    painter->restore();
}

QPoint PaintWidget::getClickPoint(int x, int y)
{
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 9; ++j)
        {
            int ty = i * delta_x + offset;
            int tx = j * delta_y + offset;

            if((ty - y) * (ty - y) + (tx - x) * (tx - x) <= radius * radius)
            {
                if(m_playerColor == BLACK)
                    return QPoint(i, j);
                else
                    return QPoint(9 - i, 8 - j);
            }
        }

    return QPoint(-1, -1);
}
