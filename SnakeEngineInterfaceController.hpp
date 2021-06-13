#pragma once

#include <vector>

#include "SnecObserver.hpp"
#include "WindowHandler.hpp"
#include "SnakeEngine.hpp"
#include "SnecObservable.hpp"

class SnakeEngineInterfaceController: public SnecObservable
{
private:
    SnakeEngine *m_snakeEngine = nullptr;
    WindowHandler *m_windowHandler = nullptr;

    //Global observser is a list of all the observer in the system
    std::vector<SnecObserver*> m_allObservers;
    std::vector<SnecObserver*> m_systemObservers;

    /* For SnecObservable Implementation */
    //void notifyAll(void) override;

public:
    SnakeEngineInterfaceController(SnakeEngine *snakeEngine,
                                    WindowHandler *windowHandler);
    //this runs our engine loop
    void run(void);

    const std::vector<SnecListenerCatagorization> *getListenerCatagorization();

    /* For SnecObservable Implementation */
    void sendMessage(SnecMessage message) override;
    void attach(SnecObserver *observer, std::vector<SnecListenerCatagorization> catagorizations) override;
};
