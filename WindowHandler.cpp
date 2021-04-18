#include <ncurses.h>

#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"

WindowHandler::WindowHandler()
{
    initscr();
}

WindowHandler::~WindowHandler()
{
    endwin();
}
