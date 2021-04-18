#pragma once

#include <vector>
#include "boost/multi_array.hpp"
#include "boost/array.hpp"
#include "boost/cstdlib.hpp"

#include "Snake.hpp"
#include "Tile.hpp"

typedef boost::multi_array<Tile, 2> PlayField;

class SnakeEngine
{
private:
    bool m_snakeCreatedHere = false;
    Snake *m_snake = nullptr;
    bool m_playfieldCreatedHere = false;
    //TODO: Work out the details of multi_array implementation
    PlayField *m_playfield = nullptr;
public:
    SnakeEngine(int width, int height);
    SnakeEngine(int width, int height, Snake *snake);
    SnakeEngine(Snake *snake, PlayField *playfield);
    ~SnakeEngine();
};
