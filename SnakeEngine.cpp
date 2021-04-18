#include "SnakeEngine.hpp"


SnakeEngine::SnakeEngine(int width, int height):
    m_playfield[width][height],
    m_snake(),
    m_snakeCreatedHere(true),
    m_playfieldCreatedHere(true)
{}

SnakeEngine::SnakeEngine(int width, int height, Snake *snake):
    m_playfieldCreatedHere(true)
{
    this->playfield = new std::vector();
    this->m_snake = snake;
}

SnakeEngine::SnakeEngine(Snake *snake, std::vector< std::vector< Tile > > *playfield):
{
    this->m_playfield = playfield;
    this->m_snake = snake;
}

SnakeEngine::~SnakeEngine()
{
    if(this->m_playfieldCreatedHere)
        delete this->m_playfield;
    if(this->m_snakeCreatedHere)
        delete this->m_snake;
}
