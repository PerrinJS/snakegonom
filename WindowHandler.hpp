#pragma once

#include <exception>
#include <vector>

#include <ncurses.h>

#include "SnakeEngine.hpp"
#include "SnecObserver.hpp"

namespace View
{
class Drawable
{
  public:
    virtual void redraw(void) = 0;
    // Drawable refresh
    virtual void dRefresh(void) = 0;
    virtual ~Drawable(void) = default;
};

class InterfaceElement : public Drawable
{
  public:
    virtual void setPosition(int x, int y) = 0;
    virtual Drawable *getParent(void) = 0;
    virtual ~InterfaceElement(void) override = default;
};

// TODO: Finish filling out thease classes
namespace Elements
{
class Window : public InterfaceElement
{
  private:
    Drawable *m_parent = nullptr;
    WINDOW *m_thisWin = nullptr;
    std::vector<InterfaceElement *> m_childElements;

  public:
    Window(Drawable *parent, int xSize, int ySize, int xPos, int yPos);
    ~Window(void) override;
    void setPosition(int x, int y) override;
    Drawable *getParent(void) override;
    void redraw(void) override;
    void dRefresh(void) override;
};

class Label : public InterfaceElement
{
  public:
    Label(int xSize, int ySize, int xPos, int yPos);
    ~Label(void) override;
    void setPosition(int x, int y) override;
    Drawable *getParent(void) override;
    void redraw(void) override;
    void dRefresh(void) override;
};

class Button : public InterfaceElement
{
  public:
    Button(int xSize, int ySize, int xPos, int yPos);
    ~Button(void) override;
    void setPosition(int x, int y) override;
    Drawable *getParent(void) override;
    void redraw(void) override;
    void dRefresh(void) override;
};
} // namespace Elements

/* TODO: make the window handler a singleton since only one 'instance' of
 * ncurses can exist at once */
class WindowHandler : public SnecObserver, public Drawable
{
  private:
    // the default values of thease are set int the cpp file
    static WindowHandler *masterWindowHandler;

    // back pointer to the controller
    SnecObservable *engineInterfaceController = nullptr;

  protected:
    int xwid = 0;
    int ywid = 0;
    WINDOW *playAreaWindow = nullptr;

    WindowHandler(void);
    // the return value is weather the size changed from the previous value
    bool updatexywid(void);
    // Gets and handles all key events from ncurses
    void handleKeyEvent(int toHandle);

    /* Implementation of Drawable */
    // Builds / recreats the interface from scratch
    void redraw(void) override;
    // For handling the UPDATE message
    void dRefresh(void) override;

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

} // namespace View
