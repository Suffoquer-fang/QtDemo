#ifndef STONE_H
#define STONE_H

//1-将
//2-士
//3-象
//4-马
//5-车
//6-炮
//7-兵
const int offset = 75;
const int delta_x = 80;
const int delta_y = 83;
const int radius = 35;

enum StoneType
{
    STONE_JIANG = 0,
    STONE_SHI,
    STONE_XIANG,
    STONE_MA,
    STONE_JU,
    STONE_PAO,
    STONE_BING
};

enum StoneColor
{
    RED = 0,
    BLACK,
    EMPTY
};


class StoneClass
{
public:
    StoneClass(StoneType type, StoneColor color) {m_type = type; m_color = color; m_isSelected = false;}
    StoneClass(int id, StoneColor color)
    {
        m_color = color; m_isSelected = false;
        switch (id) {
        case 1:
            m_type = STONE_JIANG;
            break;
        case 2:
            m_type = STONE_SHI;
            break;
        case 3:
            m_type = STONE_XIANG;
            break;
        case 4:
            m_type = STONE_MA;
            break;
        case 5:
            m_type = STONE_JU;
            break;
        case 6:
            m_type = STONE_PAO;
            break;
        case 7:
            m_type = STONE_BING;
            break;
        default:
            break;
        }
    }
    ~StoneClass() {}

private:
    StoneType m_type;
    //bool m_isAlive;
    bool m_isSelected;
    int m_x, m_y;
    StoneColor m_color;

public:
    void select() {m_isSelected = true;}
    void disselect() {m_isSelected = false;}
    void reverse() {m_isSelected = !m_isSelected;}

    //void setAlive(bool f) {m_isAlive = f;}
    //void kill() {m_isAlive = false;}
    void setPos(int x, int y) {m_x = x; m_y = y;}

    StoneType type() {return m_type;}
    int x() {return m_x;}
    int y() {return m_y;}

    bool isSelected() {return m_isSelected;}
    //bool isAlive() {return m_isAlive;}
    StoneColor color() {return m_color;}

};


class StoneMove
{
private:
    int m_old_x, m_old_y;
    int m_new_x, m_new_y;

public:
    int old_x() {return m_old_x;}
    int old_y() {return m_old_y;}
    int new_x() {return m_new_x;}
    int new_y() {return m_new_y;}

    void set(int x, int y, int x1, int y1)
    {
        m_old_x = x;
        m_old_y = y;
        m_new_x = x1;
        m_new_y = y1;
    }

};

#endif // STONE_H
