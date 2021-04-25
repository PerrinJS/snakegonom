#include <ncurses.h>

#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"


int WindowHandler::refCount = 0;
WindowHandler *WindowHandler::masterWindowHandler = nullptr;

WindowHandler::WindowHandler()
{
    initscr();
    //send keys as they are pressed
    cbreak();
    noecho();
    //TODO: this should be only enabled on the playwindow when we make it
    //enable arrow keys on stdscr
    keypad(stdscr, TRUE);

    this->masterWindowHandler = this;
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

WindowHandler *WindowHandler::getWindowHandlerSingleton()
{
    if(WindowHandler::masterWindowHandler == nullptr)
        WindowHandler::masterWindowHandler = new WindowHandler();
    WindowHandler::refCount++;
    return WindowHandler::masterWindowHandler;
}

void WindowHandler::dropRef()
{
    if(refCount == 1)
    {
        delete WindowHandler::masterWindowHandler;
        WindowHandler::refCount--;
    }
    else if(refCount > 1)
        WindowHandler::refCount--;
    else
    {
        throw WindowHandlerRefCountException();
    }
}

const char* WindowHandlerRefCountException::what() const noexcept
{
    return "negative ref count";
}
