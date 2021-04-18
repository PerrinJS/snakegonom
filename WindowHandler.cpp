#include <ncurses.h>

#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"

WindowHandler::WindowHandler()
{
    initscr();
    //send keys as they are pressed
    cbreak();
    noecho();
    //TODO: this should be only enabled on the playwindow when we make it
    //enable arrow keys on stdscr
    keypad(stdscr, TRUE);

}

WindowHandler::~WindowHandler(void)
{
    endwin();
}

void WindowHandler::pause(void)
{
    //TODO: this is just till we have the interface filled out more
    printw("paused");
    getch();
    //FIXME: this is for testing
    getch();
}

std::vector<int> WindowHandler::getPlayAreaDimen(void)
{
    //TODO: make this actuall equate to how it will work
    std::vector<int> ret;
    ret.push_back(0);
    ret.push_back(0);
    return ret;
}
