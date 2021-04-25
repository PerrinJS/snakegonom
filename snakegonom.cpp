#include <ncurses.h>

#include <iostream>

#include "SnakeEngine.hpp"
#include "WindowHandler.hpp"
#include "SnakeEngineInterfaceController.hpp"

int main(void)
{
    WindowHandler *wh = WindowHandler::getWindowHandlerSingleton();
    auto playAreaSz = wh->getPlayAreaDimen();
    if(playAreaSz.size() >= 2)
    {
        SnakeEngine *se = new SnakeEngine(playAreaSz[0], playAreaSz[1]);

        SnakeEngineInterfaceController *controller =
            new SnakeEngineInterfaceController(se, wh);
        controller->run();

        delete controller;
        controller = nullptr;
        delete se;
        se = nullptr;
        wh->dropRef();
        wh = nullptr;
    }
    else
    {
        wh->dropRef();
        wh = nullptr;

        //We can only do this (use cout) because we deleted the window handler
        std::cout << "Error: could not get screen size" << std::endl;
    }

    return 0;
}
