#ifndef GAME_H
#define GAME_H

#include <mapclass.h>
class Game
{
public:
    Game();


    void startNewGame();
    void startLoadedGame(MapClass *newMap, StoneColor color);

    void nextRound();
    bool moveStone(StoneClass *stone, int tx, int ty);

    void setCurrColor(StoneColor color) {m_currColor = color;}

    MapClass* map() {return m_map;}
    StoneColor currColor() {return m_currColor;}

    bool isGameEnd() {return m_isGameEnd;}
    void endGame() {m_isGameEnd = true;}

    StoneColor winnerColor() {return m_winnerColor;}
    void setWinner(StoneColor color) {m_winnerColor = color;}

private:

    MapClass *m_map;
    StoneColor m_currColor;

    bool m_isGameEnd;

    StoneColor m_winnerColor;


};

#endif // GAME_H
