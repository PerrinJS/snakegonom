#pragma once

#include <exception>
#include <vector>

#include <ncurses.h>

#include "SnakeEngine.hpp"
#include "SnecObserver.hpp"

/* TODO: make the window handler a singleton since only one 'instance' of
 * ncurses can exist at once */
class WindowHandler : public SnecObserver
{
  private:
    // the default values of thease are set int the cpp file
    static WindowHandler *masterWindowHandler;

    SnecObservable *engineInterfaceController = nullptr;

    int xwid = 0;
    int ywid = 0;
    WINDOW *playAreaWindow = nullptr;

    WindowHandler(void);
    // the return value is weather the size changed from the previous value
    bool updatexywid(void);
    // Builds / recreats the interface from scratch
    void redraw(void);
    // For handling the UPDATE message
    void whUpdate(void);
    // Gets and handles all key events from ncurses
    void handleKeyEvent(int toHandle);

  public:
    ~WindowHandler(void) override;

    void pause(void);
    std::vector<int> getPlayAreaDimen(void) const;

    static WindowHandler *getWindowHandlerSingleton(void);

    /* SnecObserver Implementation */
    void sendMessage(SnecMessage message) override;
    void linkObservable(SnecObservable *ovservable) override;
    void unlinkObservable(void) override;
};
