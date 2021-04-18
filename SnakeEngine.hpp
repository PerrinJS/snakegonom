#pragma once

#include <vector>

#include "Snake.hpp"

class Tile;

class SnakeEngine
{
private:
    bool m_snakeCreatedHere = false;
    Snake *m_snake = nullptr;
    bool m_playfieldCreatedHere = false;
    Tile m_playfield[][] = nullptr;
public:
    SnakeEngine(int width, int height);
    SnakeEngine(int width, int height, Snake *snake);
    SnakeEngine(Snake *snake, std::vector< std::vector< Tile > > *playfield);
    ~SnakeEngine();
};
