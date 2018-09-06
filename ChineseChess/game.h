#ifndef GAME_H
#define GAME_H

#include <mapclass.h>
class Game
{
public:
    Game();


    void startNewGame();
    void startLoadedGame();

    void nextRound();
    bool moveStone(StoneClass *stone, int tx, int ty);



    MapClass* map() {return m_map;}
    StoneColor currColor() {return m_currColor;}
    //StoneColor playerColor() {return m_playerColor;}

    //bool isMyTurn() {return m_currColor == m_playerColor;}

    //void setPlayerColor(StoneColor color) {m_playerColor = color;}


private:

    MapClass *m_map;
    StoneColor m_currColor;
    //StoneColor m_playerColor;


};

#endif // GAME_H
