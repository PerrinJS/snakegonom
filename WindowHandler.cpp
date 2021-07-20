#include <cassert>
#include <cstdio>
#include <string>

#include <ncurses.h>

#include "SnakeEngine.hpp"
#include "SnecObservable.hpp"
#include "WindowHandler.hpp"

namespace View
{
WindowHandler *WindowHandler::masterWindowHandler = nullptr;

WindowHandler::WindowHandler(void)
{
    initscr();
    // send keys as they are pressed
    cbreak();
    noecho();
    timeout(200);
    // TODO: this should be only enabled on the playwindow when we make it
    // enable arrow keys on stdscr
    keypad(stdscr, TRUE);

    /* SETUP WINDOWS AND ATTRIBUTES */
    updatexywid();
    redraw();

    this->masterWindowHandler = this;
}

WindowHandler::~WindowHandler(void)
{
    if (this->playAreaWindow != nullptr)
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
    if ((oldx != this->xwid) || (oldy != this->ywid))
    {
        changed = true;
    }

    return changed;
}

void WindowHandler::redraw(void)
{
    erase();
    werase(this->playAreaWindow);
    if (this->playAreaWindow != nullptr)
    {
        delwin(this->playAreaWindow);
        this->playAreaWindow = nullptr;
    }
    // we leave a free line at the top of the screen as a "title"
    this->playAreaWindow =
        newwin(static_cast<int>(ywid - 2), static_cast<int>(xwid - 1), 1, 0);
    box(this->playAreaWindow, 0, 0);
}

void WindowHandler::dRefresh(void)
{
    handleKeyEvent(getch());

    /* TODO: This is just while were testing, eventually we should do something
     * else when the screen is resized */
    if (updatexywid())
    {
        redraw();
    }

    mvprintw(0, 0, "paused wid:%d, height:%d", xwid, ywid);
    // ncurses refresh
    refresh();
    if (this->playAreaWindow != nullptr)
    {
        wmove(this->playAreaWindow, 0, 0);
        wprintw(this->playAreaWindow, "test");
        wrefresh(this->playAreaWindow);
    }
}

void WindowHandler::handleKeyEvent(int toHandle)
{
    switch (toHandle)
    {
    case KEY_UP:
    {
        // TODO: this is just while we develop the rest of the system
        if (this->engineInterfaceController)
        {
            printw("KeyPressed %d", toHandle);
            this->engineInterfaceController->sendMessage(
                Message{.type = STOP, .state = nullptr});
        }
        break;
    }
    default:
        break;
    }
}

void WindowHandler::pause(void) { dRefresh(); }

std::vector<int> WindowHandler::getPlayAreaDimen(void) const
{
    // TODO: make this actuall equate to how it will work
    std::vector<int> ret;
    ret.push_back(0);
    ret.push_back(0);
    return ret;
}

WindowHandler *WindowHandler::getWindowHandlerSingleton(void)
{
    if (WindowHandler::masterWindowHandler == nullptr)
        WindowHandler::masterWindowHandler = new WindowHandler();
    return WindowHandler::masterWindowHandler;
}

/* SnecObserver Implementation */
void WindowHandler::sendMessage(SnecMessage message)
{
    switch (message.type)
    {
    case PAUSE:
        this->pause();
        break;
    case UPDATE:
        this->dRefresh();
        break;
    // TODO: fill in what happends here
    case STATEINFO:
    case INTERFACEINFO:
    case STOP:
        break;
    }
}

void WindowHandler::linkObservable(SnecObservable *ovservable)
{
    if (ovservable)
    {
        this->engineInterfaceController = ovservable;
    }
}

void WindowHandler::unlinkObservable(void)
{
    if (this->engineInterfaceController)
    {
        this->engineInterfaceController = nullptr;
    }
}

} // namespace View
