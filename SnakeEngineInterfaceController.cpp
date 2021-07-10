#include "SnakeEngineInterfaceController.hpp"
#include "SnecObserver.hpp"
#include <algorithm>

SnakeEngineInterfaceController::SnakeEngineInterfaceController(
    SnakeEngine *snakeEngine, WindowHandler *windowHandler)
    : m_allObservers(), m_systemObservers()
{
    this->m_snakeEngine = snakeEngine;
    this->m_windowHandler = windowHandler;

    this->m_allObservers.push_back(m_snakeEngine);
    this->m_allObservers.push_back(m_windowHandler);
    this->m_systemObservers.push_back(m_snakeEngine);
    this->m_systemObservers.push_back(m_windowHandler);
}

void SnakeEngineInterfaceController::run()
{
    // TODO: this is for testing; tell all listeners to pause
    for (int i = 0; i < 5; i++)
    {
        std::for_each(this->m_allObservers.begin(), this->m_allObservers.end(),
                      [](SnecObserver *o)
                      {
                          o->sendMessage(SnecMessage{
                              .type = UPDATE,
                              .state = nullptr,
                          });
                      });
    }

    std::for_each(this->m_allObservers.begin(), this->m_allObservers.end(),
                  [](SnecObserver *o)
                  {
                      o->sendMessage(SnecMessage{
                          .type = PAUSE,
                          .state = nullptr,
                      });
                  });
}

/* For SnecObservable Implementation */
void SnakeEngineInterfaceController::sendMessage(SnecMessage message)
{
    switch (message.type)
    {
    // TODO: actually do something with this
    case UPDATE:
        break;
    case STATEINFO:
        break;
    case INTERFACEINFO:
        break;
    case PAUSE:
        break;
    }
}

void SnakeEngineInterfaceController::attach(
    SnecObserver *observer,
    std::vector<SnecListenerCatagorization> catagorizations)
{
    std::for_each(catagorizations.begin(), catagorizations.end(),
                  [&](SnecListenerCatagorization catagory)
                  {
                      switch (catagory)
                      {
                      case ALL:
                      {
                          this->m_allObservers.push_back(observer);
                          break;
                      }
                      case SYSTEM:
                      {
                          this->m_systemObservers.push_back(observer);
                          break;
                      }
                          /*TODO: get this to compile
                          default:
                          {
                              //TODO: create an actual exception
                              throw std::exception();
                          }*/
                      }
                  });
}
