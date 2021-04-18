#pragma once

#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"

class SnakeEngineInterfaceController
{
private:
    SnakeEngine *m_snakeEngine = nullptr;
    WindowHandler *m_windowHandler = nullptr;
public:
    SnakeEngineInterfaceController(SnakeEngine *snakeEngine,
                                    WindowHandler *windowHandler);
    //this runs our engine loop
    void run(void);
};
