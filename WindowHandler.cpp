#include <cassert>

#include <ncurses.h>

#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"

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

    /* SETUP WINDOWS AND ATTRIBUTES */
    updatexywid();
    //the one at the end means we write the box starting at y=2
    this->playAreaWindow = newwin(static_cast<int>(ywid/2)-1, static_cast<int>(xwid/2)-1, 1, 0);
    box(this->playAreaWindow, 0, 0);

    this->masterWindowHandler = this;
}

WindowHandler::~WindowHandler(void)
{
    if(this->playAreaWindow != nullptr)
    {
        delwin(this->playAreaWindow);
        this->playAreaWindow = nullptr;
    }
    endwin();
}

void WindowHandler::updatexywid(void)
{
    getmaxyx(stdscr, ywid, xwid);
}

void WindowHandler::pause(void)
{
    /* TODO: this is just till we have the interface filled out more and have
     * a draw function */
    updatexywid();
    printw("paused wid:%d, height:%d", xwid, ywid);
    refresh();
    if(this->playAreaWindow != nullptr)
    {
        wprintw(this->playAreaWindow, "test");
        wrefresh(this->playAreaWindow);
    }
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
    return WindowHandler::masterWindowHandler;
}

/* SnecObserver Implementation */
void WindowHandler::sendMessage(SnecMessage message)
{
    switch (message.type) {
        case PAUSE:
            this->pause();
            break;
        
        //TODO: fill in what happends here
        case UPDATE:
        case STATEINFO:
        case INTERFACEINFO:
            break;
    }

} 
