#include "SnakeEngineInterfaceController.hpp"
#include <algorithm>

SnakeEngineInterfaceController::SnakeEngineInterfaceController(SnakeEngine *snakeEngine,
                                                               WindowHandler *windowHandler):
                                                               m_observers()
{
   this->m_snakeEngine = snakeEngine;
   this->m_windowHandler = windowHandler;

   this->m_observers.push_back(m_snakeEngine);
   this->m_observers.push_back(m_windowHandler);
}

void SnakeEngineInterfaceController::run()
{
    //TODO: this is for testing; tell all listeners to pause
    std::for_each(this->m_observers.begin(), this->m_observers.end(),
    [](SnecObserver* o){
        o->sendMessage(
            SnecMessage
            {
                .type = PAUSE,
                .state = nullptr,
            }
        );
    });
}

/* For SnecObservable Implementation */
void SnakeEngineInterfaceController::sendMessage(SnecMessage message)
{
    /* TODO: this is the main message handler here we will forward all
     * messages to the appropriate objects */
}

void SnakeEngineInterfaceController::attach(SnecObserver *observer)
{
    if(observer != nullptr)
    {
        this->m_observers.push_back(observer);
    }
    else
    {
        //TODO: make a real exception
        throw std::exception();
    }
}
