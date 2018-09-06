#include "game.h"

Game::Game()
{
    m_map = new MapClass();
    m_map->initMap();
    m_currColor = RED;
    //m_playerColor = RED;
}

void Game::startNewGame()
{
    m_map->initMap();
}

void Game::startLoadedGame()
{
    //
}

void Game::nextRound()
{
    m_currColor = (m_currColor == RED) ? BLACK : RED;
    //m_playerColor = m_currColor;
    //
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


