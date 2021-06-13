#pragma once

#include <vector>
#include "boost/multi_array.hpp"
#include "boost/array.hpp"
#include "boost/cstdlib.hpp"

#include "Snake.hpp"
#include "Tile.hpp"
#include "SnecObserver.hpp"

typedef boost::multi_array<Tile, 2> PlayField;

class SnakeEngine: public SnecObserver
{
private:
    bool m_snakeCreatedHere = false;
    Snake *m_snake = nullptr;
    bool m_playfieldCreatedHere = false;
    //TODO: Work out the details of multi_array implementation
    PlayField *m_playfield = nullptr;

    void seUpdate(void);
public:
    SnakeEngine(int width, int height);
    SnakeEngine(int width, int height, Snake *snake);
    SnakeEngine(Snake *snake, PlayField *playfield);
    ~SnakeEngine(void) override;

    void pause(void);

    /* SnecObserver Implementation */
    void sendMessage(SnecMessage message) override;
};
