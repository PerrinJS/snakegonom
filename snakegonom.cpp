#include <cassert>
#include <iostream>

#include <ncurses.h>

#include "SnakeEngine.hpp"
#include "SnakeEngineInterfaceController.hpp"
#include "WindowHandler.hpp"

// Rember to take adventage of the new observer infestructure
int main(void)
{
    auto *wh = View::WindowHandler::getWindowHandlerSingleton();
    auto playAreaSz = wh->getPlayAreaDimen();

    SnakeEngine *se =
        new SnakeEngine(std::get<0>(playAreaSz), std::get<1>(playAreaSz));

    SnakeEngineInterfaceController *controller =
        new SnakeEngineInterfaceController(se, wh);

    wh->linkObservable(controller);
    controller->run();

    delete controller;
    controller = nullptr;
    delete se;
    se = nullptr;
    delete wh;
    wh = nullptr;

    return 0;
}
