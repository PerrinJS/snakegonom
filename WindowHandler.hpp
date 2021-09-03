#pragma once

#include <exception>
#include <functional>
#include <tuple>
#include <vector>

#include <ncurses.h>

#include "SnakeEngine.hpp"
#include "SnecObserver.hpp"

namespace View
{

typedef long InterfaceElementID;

class Drawable
{
  public:
    // TODO: move thease to protected onece applyBreadthFirst is implemented
    virtual void redraw(void) = 0;
    // Drawable refresh
    virtual void dRefresh(void) = 0;

    // TODO: unmask thease once the above changes have been made
    /* virtual void refreshAboveElements(void) = 0;
    virtual void clearAboveElements(void) = 0; */

    virtual void setText(int x, int y, std::string str) = 0;
    virtual std::tuple<int, int> getGlobalPos(void) = 0;

    virtual ~Drawable(void) = default;
};

class InterfaceElement : public Drawable
{
  protected:
    static InterfaceElementID TOTAL_ELEMENTS;
    const InterfaceElementID interfaceElemId;

    std::vector<InterfaceElement *> childElements;

    InterfaceElement(void);

  public:
    /* Pure virtual functions */
    virtual void setPosition(int x, int y) = 0;
    virtual std::tuple<int, int> getPosition(void) = 0;
    virtual Drawable *getParent(void) = 0;

    /* Concrete functions */
    // We still don't need a constructor because our container classes do
    // cleanup
    ~InterfaceElement(void) override = default;

    // For applying drawing functions that affect the depth of the items on scr
    static void
    applyBreadthFirst(std::function<void(InterfaceElement *)> *toApply,
                      std::vector<InterfaceElement *> children);

    /* Searches child elements depth first for an element with the specified id
     * If the specified id is not found then return a nullptr */
    InterfaceElement *getElementWithId(InterfaceElementID id);
    InterfaceElementID getElementId(void);
    std::vector<InterfaceElement *> getChildElements(void);
    void addChildElement(InterfaceElement *element);
};

// TODO: Finish filling out thease classes
namespace Elements
{
class Window : public InterfaceElement
{
  private:
    Drawable *parent = nullptr;
    WINDOW *thisWin = nullptr;

  protected:
    int xwid = 0;
    int ywid = 0;

  public:
    Window(Drawable *wParent, int xSize, int ySize, int xPos, int yPos);
    ~Window(void) override;
    void setText(int x, int y, std::string str) override;
    void setPosition(int x, int y) override;
    std::tuple<int, int> getPosition(void) override;
    Drawable *getParent(void) override;
    void redraw(void) override;
    std::tuple<int, int> getGlobalPos(void) override;
    void dRefresh(void) override;

    void setSize(int xSize, int ySize);
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

/* For spacing an interface element up a level. It essentially ammounts to a
 * blank node in the tree storing more branches at the above level */
class Blank : public InterfaceElement
{
  public:
    /* All thease functions are blank (do nothing) */
    Blank(int xSize, int ySize, int xPos, int yPos);
    ~Blank(void) override;
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
    bool running = true;
    int xwid = 0;
    int ywid = 0;
    std::vector<InterfaceElement *> childGuiElements;

    /* Specific Window elements */
    Elements::Window *playAreaWindow = nullptr;

    WindowHandler(void);
    // the return value is weather the size changed from the previous value
    bool updatexywid(void);
    // Gets and handles all key events from ncurses
    void handleKeyEvent(int toHandle);

    /* Functions for the different screens */
    void openPausedWindow(void);

    /* Implementation of Drawable */
    // Builds / recreats the interface from scratch
    void redraw(void) override;
    // Allows for text to be written starting at a cirtain position
    void setText(int x, int y, std::string str) override;
    // In this case because this is the root window this will always return
    // (0,0)
    std::tuple<int, int> getGlobalPos(void) override;
    // For handling the UPDATE message
    void dRefresh(void) override;

  public:
    ~WindowHandler(void) override;

    void pause(void);
    std::tuple<int, int> getPlayAreaDimen(void) const;

    static WindowHandler *getWindowHandlerSingleton(void);

    /* SnecObserver Implementation */
    void sendMessage(SnecMessage message) override;
    void linkObservable(SnecObservable *ovservable) override;
    void unlinkObservable(void) override;
};

} // namespace View
