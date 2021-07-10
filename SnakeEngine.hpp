#pragma once

#include "boost/array.hpp"
#include "boost/cstdlib.hpp"
#include "boost/multi_array.hpp"
#include <vector>

#include "Snake.hpp"
#include "SnecObserver.hpp"
#include "Tile.hpp"

// TODO: find a better home for this declaration
namespace GEntity
{
typedef boost::multi_array<Tile, 2> PlayField;
}

class SnakeEngine : public SnecObserver
{
  private:
    bool m_snakeCreatedHere = false;
    GEntity::Snake *m_snake = nullptr;
    bool m_playfieldCreatedHere = false;
    // TODO: Work out the details of multi_array implementation
    GEntity::PlayField *m_playfield = nullptr;

    void seUpdate(void);

  public:
    SnakeEngine(int width, int height);
    SnakeEngine(int width, int height, GEntity::Snake *snake);
    SnakeEngine(GEntity::Snake *snake, GEntity::PlayField *playfield);
    ~SnakeEngine(void) override;

    void pause(void);

    /* SnecObserver Implementation */
    void sendMessage(SnecMessage message) override;
};
