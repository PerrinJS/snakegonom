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

    std::vector<SnecObserver*> m_observers;

    /* For SnecObservable Implementation */
    //void notifyAll(void) override;

public:
    SnakeEngineInterfaceController(SnakeEngine *snakeEngine,
                                    WindowHandler *windowHandler);
    //this runs our engine loop
    void run(void);


    /* For SnecObservable Implementation */
    void sendMessage(SnecMessage message) override;
    void attach(SnecObserver *observer) override;
};
