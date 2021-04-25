#pragma once

#include <vector>
#include <exception>

#include "SnakeEngine.hpp"

/* TODO: make the window handler a singleton since only one 'instance' of
 * ncurses can exist at once */
class WindowHandler
{
private:
    static int refCount;
    static WindowHandler *masterWindowHandler;
    WindowHandler(void);
public:
    ~WindowHandler(void);

    void pause(void);
    std::vector<int> getPlayAreaDimen(void);

    static WindowHandler *getWindowHandlerSingleton();
    void dropRef();
};

class WindowHandlerRefCountException: public std::exception
{
    virtual const char* what() const noexcept override;
};
