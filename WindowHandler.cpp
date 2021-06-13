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
    redraw();

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

bool WindowHandler::updatexywid(void)
{
    int oldx = this->xwid, oldy = this->ywid;
    bool changed = false;
    getmaxyx(stdscr, ywid, xwid);
    if((oldx != this->xwid) || (oldy != this->ywid))
    {
        changed = true;
    }

    return changed;
}

void WindowHandler::redraw(void)
{
    erase();
    werase(this->playAreaWindow);
    if(this->playAreaWindow != nullptr)
    {
        delwin(this->playAreaWindow);
        this->playAreaWindow = nullptr;
    }
    //we leave a free line at the top of the screen as a "title"
    this->playAreaWindow = newwin(static_cast<int>(ywid-2), static_cast<int>(xwid-1), 1, 0);
    box(this->playAreaWindow, 0, 0);
}

void WindowHandler::pause(void)
{
    whUpdate();
}

void WindowHandler::whUpdate(void)
{
    /* TODO: This is just while were testing, eventually we should do something
     * else when the screen is resized */
    if(updatexywid())
    {
        redraw();
    }
    printw("paused wid:%d, height:%d", xwid, ywid);
    //ncurses refresh
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
        case UPDATE:
            this->whUpdate();
            break;
        //TODO: fill in what happends here
        case STATEINFO:
        case INTERFACEINFO:
            break;
    }

} 
