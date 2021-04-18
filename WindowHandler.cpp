#include <ncurses.h>

#include "WindowHandler.hpp"


WindowHandler::WindowHandler()
{
    initscr();
}

WindowHandler::~WindowHandler()
{
    endwin();
}
