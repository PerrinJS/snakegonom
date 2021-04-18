#include "SnakeEngineInterfaceController.hpp"

SnakeEngineInterfaceController::SnakeEngineInterfaceController(SnakeEngine *snakeEngine,
                                                                WindowHandler *windowHandler)
{
   this->m_snakeEngine = snakeEngine;
   this->m_windowHandler = windowHandler;
}

void SnakeEngineInterfaceController::run()
{
    this->m_snakeEngine->pause();
    this->m_windowHandler->pause();
}

