#include "game.h"

Game::Game()
{
    m_map = new MapClass();
    m_map->initMap();
    m_currColor = RED;
    //m_playerColor = RED;
    m_isGameEnd = false;
}

void Game::startNewGame()
{
    m_map->initMap();
    m_isGameEnd = false;
    m_currColor = RED;
}

void Game::startLoadedGame(MapClass *newMap, StoneColor color)
{
    //
    m_map = newMap;
    m_isGameEnd = false;
    m_currColor = color;
}

void Game::nextRound()
{
    if(m_map->getWinner() == EMPTY)
        m_currColor = (m_currColor == RED) ? BLACK : RED;
    else
    {
        setWinner(m_map->getWinner());
        endGame();
    }
}

bool Game::moveStone(StoneClass *stone, int tx, int ty)
{
    if(m_map->moveStone(stone, tx, ty))
    {
        nextRound();
        return true;
    }

    return false;
}



