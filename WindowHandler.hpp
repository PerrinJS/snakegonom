#pragma once

#include <vector>
#include <exception>

#include <ncurses.h>

#include "SnakeEngine.hpp"
#include "SnecObserver.hpp"

/* TODO: make the window handler a singleton since only one 'instance' of
 * ncurses can exist at once */
class WindowHandler: public SnecObserver
{
private:
    //the default values of thease are set int the cpp file
    static WindowHandler *masterWindowHandler;

    int xwid = 0;
    int ywid = 0;
    WINDOW *playAreaWindow = nullptr;

    WindowHandler(void);
    void updatexywid(void);
public:
    ~WindowHandler(void) override;

    void pause(void);
    std::vector<int> getPlayAreaDimen(void);

    static WindowHandler *getWindowHandlerSingleton();

    /* SnecObserver Implementation */
    void sendMessage(SnecMessage message) override;
};
