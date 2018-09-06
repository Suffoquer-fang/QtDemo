#include "mapclass.h"

MapClass::MapClass()
{
    m_red.push_back(new StoneClass(1, RED));
    m_black.push_back(new StoneClass(1, BLACK));

    for(int i = 1; i < 6; ++i)
    {
        m_red.push_back(new StoneClass(i + 1, RED));
        m_red.push_back(new StoneClass(i + 1, RED));
        m_black.push_back(new StoneClass(i + 1, BLACK));
        m_black.push_back(new StoneClass(i + 1, BLACK));
    }

    for(int i = 11; i < 16; ++i)
    {
        m_red.push_back(new StoneClass(7, RED));
        m_black.push_back(new StoneClass(7, BLACK));
    }

    m_recentMove = new StoneMove;
    initMap();
    m_focusStone = nullptr;
}

void MapClass::initMap()
{
    //将
    m_red[0]->setPos(0, 4);
    m_black[0]->setPos(9, 4);

    //士
    m_red[1]->setPos(0, 3);     m_black[1]->setPos(9, 3);
    m_red[2]->setPos(0, 5);     m_black[2]->setPos(9, 5);
    //象
    m_red[3]->setPos(0, 2);     m_black[3]->setPos(9, 2);
    m_red[4]->setPos(0, 6);     m_black[4]->setPos(9, 6);
    //马
    m_red[5]->setPos(0, 1);     m_black[5]->setPos(9, 1);
    m_red[6]->setPos(0, 7);     m_black[6]->setPos(9, 7);
    //车
    m_red[7]->setPos(0, 0);     m_black[7]->setPos(9, 0);
    m_red[8]->setPos(0, 8);     m_black[8]->setPos(9, 8);
    //炮
    m_red[9]->setPos(2, 1);     m_black[9]->setPos(7, 1);
    m_red[10]->setPos(2, 7);    m_black[10]->setPos(7, 7);

    //兵
    for(int i = 0; i < 5; ++i)
    {
        m_red[11 + i]->setPos(3, 2 * i);
        m_black[11 + i]->setPos(6, 2 * i);
    }

    m_recentMove->set(-1, -1, -1, -1);
}

bool MapClass::isInsideMap(int x, int y)
{
    return (0 <= x && x <= 9 && 0 <= y && y <= 8);
}

bool MapClass::isInsideRedArea(int x, int y)
{
    return (0 <= x && x <= 4 && 0 <= y && y <= 8);
}

bool MapClass::isInsideColorArea(int x, int y, StoneColor color)
{
    if(color == RED)
        return isInsideRedArea(x, y);
    else
        return !isInsideRedArea(x, y);
}

StoneClass* MapClass::getStoneAtPoint(int x, int y)
{
    for(int i = 0; i < m_red.size(); ++i)
    {
        if(m_red[i]->x() == x && m_red[i]->y() == y)
            return m_red[i];
    }
    for(int i = 0; i < m_black.size(); ++i)
    {
        if(m_black[i]->x() == x && m_black[i]->y() == y)
            return m_black[i];
    }

}

StoneColor MapClass::getColorAtPoint(int x, int y)
{
    for(int i = 0; i < m_red.size(); ++i)
    {
        if(m_red[i]->x() == x && m_red[i]->y() == y)
            return RED;
    }
    for(int i = 0; i < m_black.size(); ++i)
    {
        if(m_black[i]->x() == x && m_black[i]->y() == y)
            return BLACK;
    }
    return EMPTY;
}

void MapClass::GetMoveArea_JU(StoneClass* stone, QVector<QPoint>& area)
{
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int x, y;
    for(int k = 0; k < 4; ++k)
    {
        int x = stone->x();
        int y = stone->y();
        x += dx[k], y += dy[k];
        while(isInsideMap(x, y) && getColorAtPoint(x, y) == EMPTY)
        {
            area.push_back(QPoint(x, y));
            x += dx[k], y += dy[k];
        }
        if(isInsideMap(x, y) && getColorAtPoint(x, y) != stone->color())
            area.push_back(QPoint(x, y));

    }
}

void MapClass::GetMoveArea_MA(StoneClass* stone, QVector<QPoint>& area)
{
    int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

    for(int k = 0; k < 8; ++k)
    {
        int x = stone->x();
        int y = stone->y();
        if(isInsideMap(x + dx[k], y + dy[k]) && getColorAtPoint(x + dx[k], y + dy[k]) != stone->color())
        {
            if((k == 0 || k == 2) && getColorAtPoint(x, y + 1) != EMPTY)    continue;
            if((k == 1 || k == 3) && getColorAtPoint(x, y - 1) != EMPTY)    continue;
            if((k == 4 || k == 5) && getColorAtPoint(x + 1, y) != EMPTY)    continue;
            if((k == 6 || k == 7) && getColorAtPoint(x - 1, y) != EMPTY)    continue;

            area.push_back(QPoint(x + dx[k], y + dy[k]));
        }
    }
}

void MapClass::GetMoveArea_XIANG(StoneClass* stone, QVector<QPoint>& area)
{
    int dx[] = {2, 2, -2, -2};
    int dy[] = {2, -2, 2, -2};

    for(int k = 0; k < 4; ++k)
    {
        if(isInsideColorArea(stone->x() + dx[k], stone->y() + dy[k], stone->color()) && getColorAtPoint(stone->x() + dx[k], stone->y() + dy[k]) != stone->color())
        {
            if(getColorAtPoint(stone->x() + dx[k] / 2, stone->y() + dy[k] / 2) == EMPTY)
            {
                area.push_back(QPoint(stone->x() + dx[k], stone->y() + dy[k]));
            }
        }
    }
}

void MapClass::GetMoveArea_SHI(StoneClass* stone, QVector<QPoint>& area)
{
    if(stone->x() == 0 || stone->x() == 2)
    {
        if(getColorAtPoint(1, 4) != stone->color())
            area.push_back(QPoint(1, 4));
    }else if(stone->x() == 1)
    {
        if(getColorAtPoint(0, 3) != stone->color())
            area.push_back(QPoint(0, 3));
        if(getColorAtPoint(0, 5) != stone->color())
            area.push_back(QPoint(0, 5));
        if(getColorAtPoint(2, 3) != stone->color())
            area.push_back(QPoint(2, 3));
        if(getColorAtPoint(2, 5) != stone->color())
            area.push_back(QPoint(2, 5));
    }

    if(stone->x() == 9 || stone->x() == 7)
    {
        if(getColorAtPoint(8, 4) != stone->color())
            area.push_back(QPoint(8, 4));
    }else if(stone->x() == 8)
    {
        if(getColorAtPoint(9, 3) != stone->color())
            area.push_back(QPoint(9, 3));
        if(getColorAtPoint(9, 5) != stone->color())
            area.push_back(QPoint(9, 5));
        if(getColorAtPoint(7, 3) != stone->color())
            area.push_back(QPoint(7, 3));
        if(getColorAtPoint(7, 5) != stone->color())
            area.push_back(QPoint(7, 5));
    }


}

void MapClass::GetMoveArea_JIANG(StoneClass* stone, QVector<QPoint>& area)
{
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    for(int k = 0; k < 4; ++k)
    {
        int x = stone->x() + dx[k];
        int y = stone->y() + dy[k];

        if(stone->color() == RED)
        {
            if(0 <= x && x <= 2 && 3 <= y && y <= 5 && getColorAtPoint(x, y) != RED)
                area.push_back(QPoint(x, y));
        }else
        {
            if(7 <= x && x <= 9 && 3 <= y && y <= 5 && getColorAtPoint(x, y) != BLACK)
                area.push_back(QPoint(x, y));
        }
    }
}

void MapClass::GetMoveArea_PAO(StoneClass* stone, QVector<QPoint>& area)
{
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int x, y;
    for(int k = 0; k < 4; ++k)
    {
        int x = stone->x();
        int y = stone->y();
        x += dx[k], y += dy[k];
        int cnt = 0;
        while(isInsideMap(x, y))
        {
            if(getColorAtPoint(x, y) == EMPTY)
            {
                if(cnt == 0)
                    area.push_back(QPoint(x, y));
            }
            else
            {
                cnt++;
                if(cnt == 2)
                {
                    if(getColorAtPoint(x, y) != stone->color())
                        area.push_back(QPoint(x, y));
                    break;
                }
            }

            x += dx[k], y += dy[k];
        }
    }



}

void MapClass::GetMoveArea_BING(StoneClass* stone, QVector<QPoint>& area)
{
    if(stone->color() == RED)
    {
        if(isInsideMap(stone->x() + 1, stone->y()) && getColorAtPoint(stone->x() + 1, stone->y()) != RED)
        {
            area.push_back(QPoint(stone->x() + 1, stone->y()));
        }
        if(stone->x() >= 5)
        {
            if(isInsideMap(stone->x(), stone->y() + 1) && getColorAtPoint(stone->x(), stone->y() + 1) != RED)
            {
                area.push_back(QPoint(stone->x(), stone->y() + 1));
            }
            if(isInsideMap(stone->x(), stone->y() - 1) && getColorAtPoint(stone->x(), stone->y() - 1) != RED)
            {
                area.push_back(QPoint(stone->x(), stone->y() - 1));
            }
        }
    }

    if(stone->color() == BLACK)
    {
        if(isInsideMap(stone->x() - 1, stone->y()) && getColorAtPoint(stone->x() - 1, stone->y()) != BLACK)
        {
            area.push_back(QPoint(stone->x() - 1, stone->y()));
        }
        if(stone->x() <= 4)
        {
            if(isInsideMap(stone->x(), stone->y() + 1) && getColorAtPoint(stone->x(), stone->y() + 1) != BLACK)
            {
                area.push_back(QPoint(stone->x(), stone->y() + 1));
            }
            if(isInsideMap(stone->x(), stone->y() - 1) && getColorAtPoint(stone->x(), stone->y() - 1) != BLACK)
            {
                area.push_back(QPoint(stone->x(), stone->y() - 1));
            }
        }
    }
}

bool MapClass::checkGeneralFacing()
{
    if(m_red[0]->y() != m_black[0]->y())    return false;
    for(int i = m_red[0]->x() + 1; i < m_black[0]->x(); ++i)
        if(getColorAtPoint(i, m_red[0]->y()) != EMPTY)
            return  false;
    return true;
}

void MapClass::GetMoveArea(StoneClass* stone, QVector<QPoint>& area)
{
    switch (stone->type()) {
    case STONE_JIANG:
        GetMoveArea_JIANG(stone, area);
        break;
    case STONE_XIANG:
        GetMoveArea_XIANG(stone, area);
        break;
    case STONE_JU:
        GetMoveArea_JU(stone, area);
        break;
    case STONE_MA:
        GetMoveArea_MA(stone, area);
        break;
    case STONE_PAO:
        GetMoveArea_PAO(stone, area);
        break;
    case STONE_SHI:
        GetMoveArea_SHI(stone, area);
        break;
    case STONE_BING:
        GetMoveArea_BING(stone, area);
        break;
    default:
        break;
    }

    //对将
    /*
    int x = stone->x();
    int y = stone->y();
    for(int i = 0; i < area.size(); ++i)
    {
        stone->setPos(area[i].x(), area[i].y());
        if(checkGeneralFacing())
            area.removeAt(i--);
    }

    stone->setPos(x, y);*/

    if(stone->type() == STONE_JIANG && checkGeneralFacing())
    {
        area.push_back(QPoint(enemy(stone->color()).at(0)->x(), enemy(stone->color()).at(0)->y()));
    }
}

bool MapClass::moveStone(StoneClass* stone, int target_X, int target_Y)
{
    m_focusStone = nullptr;
    if(isInsideMap(target_X, target_Y))
    {
        QVector<QPoint> area;
        GetMoveArea(stone, area);
        if(!area.contains(QPoint(target_X, target_Y)))  return false;
        int tmpx = stone->x();
        int tmpy = stone->y();
        if(getColorAtPoint(target_X, target_Y) != EMPTY)
        {
            m_black.removeOne(getStoneAtPoint(target_X, target_Y));
            m_red.removeOne(getStoneAtPoint(target_X, target_Y));
        }
        stone->setPos(target_X, target_Y);
        m_recentMove->set(tmpx, tmpy, target_X, target_Y);
        return true;
    }
    m_recentMove->set(-1, -1, -1, -1);
    return false;
}

bool MapClass::is_JIANGJUN(StoneColor color)
{
    int x = enemy(color).at(0)->x();
    int y = enemy(color).at(0)->y();

    for(int i = 0; i < ally(color).size(); ++i)
    {
        QVector<QPoint> area;
        GetMoveArea(ally(color).at(i), area);
        if(area.contains(QPoint(x, y)))
            return true;
    }

    return false;
}

StoneColor MapClass::getWinner()
{
    if(m_red[0]->type() != STONE_JIANG)
        return BLACK;
    else if(m_black[0]->type() != STONE_JIANG)
        return RED;
    else
        return EMPTY;
}
