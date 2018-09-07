#ifndef MAPCLASS_H
#define MAPCLASS_H

#include <stone.h>
#include <QVector>
#include <QPoint>

class MapClass
{
public:
    MapClass();

    void initMap();

    bool isInsideMap(int x, int y);
    bool isInsideRedArea(int x, int y);
    bool isInsideColorArea(int x, int y, StoneColor color);

    StoneClass* getStoneAtPoint(int x, int y);
    StoneColor getColorAtPoint(int x, int y);

    bool checkGeneralFacing();

    void GetMoveArea(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_JU(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_MA(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_XIANG(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_SHI(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_JIANG(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_PAO(StoneClass* stone, QVector<QPoint>& area);
    void GetMoveArea_BING(StoneClass* stone, QVector<QPoint>& area);

    bool moveStone(StoneClass* stone, int target_X, int target_Y);

    QVector<StoneClass*> red() {return m_red;}
    QVector<StoneClass*> black() {return m_black;}
    QVector<StoneClass*> enemy(StoneColor color) {return (color == RED) ? m_black : m_red;}
    QVector<StoneClass*> ally(StoneColor color) {return (color == RED) ? m_red : m_black;}
    StoneClass* focusStone() {return m_focusStone;}

    void setFocusStone(StoneClass* stone) {m_focusStone = stone;}

    StoneMove* recentMove() {return m_recentMove;}

    bool is_JIANGJUN(StoneColor color);
    StoneColor getWinner();

    void clear() {m_red.clear(); m_black.clear();}
    void addRedStone(StoneClass *stone) {m_red.push_back(stone);}
    void addBlackStone(StoneClass *stone) {m_black.push_back(stone);}

private:
    QVector<StoneClass*> m_red;
    QVector<StoneClass*> m_black;

    StoneClass *m_focusStone;

    StoneMove *m_recentMove;

};

#endif // MAPCLASS_H
