#include "SnakeEngineInterfaceController.hpp"
#include "SnecObserver.hpp"

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

    // when run is called continue untill a message is given to stop
    this->cont = true;
}

SnakeEngineInterfaceController::~SnakeEngineInterfaceController(void) 
{
    for (auto *ob : this->m_allObservers)
    {
        ob->unlinkObservable();
    }
}

void SnakeEngineInterfaceController::run(void)
{
    while (this->cont)
    {
        for (auto *o : this->m_allObservers)
        {
            o->sendMessage(SnecMessage{
                .type = UPDATE,
                .state = nullptr,
            });
        }
    }

    // TODO: implent stop in all the classes before changing this to send a stop
    // message
    for (auto *o : this->m_allObservers)
    {
        o->sendMessage(SnecMessage{
            .type = PAUSE,
            .state = nullptr,
        });
    }
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
    case STOP:
        this->cont = false;
        break;
    }
}

void SnakeEngineInterfaceController::attach(
    SnecObserver *observer,
    std::vector<SnecListenerCatagorization> catagorizations)
{
    for (auto catagory : catagorizations)
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
    }
}
