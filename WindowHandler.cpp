#include <ncurses.h>

#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"

WindowHandler::WindowHandler(SnakeEngine *engine)
{
   this->m_engine = engine;
   /* TODO: this needs to take the width and height from the engine to check the
    * playfield size can be drawn */
   this->init();
}

WindowHandler::WindowHandler()
{
    this->init();
    //get the play window width and height and put it into the engine
    //this->m_engine = new engine();
}

WindowHandler::~WindowHandler()
{
    endwin();
    if(this->m_engine != nullptr)
        delete this->m_engine;
}

void WindowHandler::init()
{
    this->init(0, 0);
}

void WindowHandler::init(int width, int height)
{
    //if one is zero all bits are zero
    bool desidePlayAreaSize = width & height;

    //TODO
    if(desidePlayAreaSize)
    {

    }
    else
    {
        initscr();
        /* TODO: build play window and figure how you going to work with width
        * and height */
    }
}
