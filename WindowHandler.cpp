#include <cassert>
#include <cstdio>
#include <string>

#include <ncurses.h>
#include <tuple>

#include "SnakeEngine.hpp"
#include "SnecObservable.hpp"
#include "WindowHandler.hpp"

namespace View
{

InterfaceElementID InterfaceElement::TOTAL_ELEMENTS = 0;

/* The only interface element field is it's id. This is taken from the
 * TOTAL_ELEMENTS static field which is then incremented ready for the next
 * elements to take that new id. */
InterfaceElement::InterfaceElement(void) : interfaceElemId(TOTAL_ELEMENTS++) {}

InterfaceElement *InterfaceElement::getElementWithId(InterfaceElementID id)
{
    InterfaceElement *ret = nullptr;

    for (auto *element : this->childElements)
    {
        if (element->interfaceElemId == id)
        {
            ret = element;
            break;
        }
        else
        {
            // depth first
            ret = element->getElementWithId(id);
            if (ret != nullptr)
                break;
        }
    }

    return ret;
}

InterfaceElementID InterfaceElement::getElementId(void)
{
    return this->interfaceElemId;
}

std::vector<InterfaceElement *> InterfaceElement::getChildElements(void)
{
    return this->childElements;
}

void InterfaceElement::addChildElement(InterfaceElement *element)
{
    if (element != nullptr)
    {
        this->childElements.push_back(element);
    }
}

namespace Elements
{
/* IMPLENENTATION OF WINDOW */
/* TODO: move the code in window handler that works with the main window into
 * here */
Window::Window(Drawable *wParent, int xSize, int ySize, int xPos, int yPos)
{
    this->xwid = xSize;
    this->ywid = ySize;
    this->parent = wParent;
    this->thisWin = newwin(ySize, xSize, yPos, xPos);
}

Window::~Window(void) { delwin(this->thisWin); }

void Window::setText(int x, int y, std::string str)
{
    mvwprintw(this->thisWin, y, x, str.c_str());
}

void Window::setPosition(int x, int y)
{
    assert(this->thisWin);
    if (this->thisWin)
    {
        auto parentPos = getParent()->getGlobalPos();
        mvwin(this->thisWin, y + std::get<1>(parentPos),
              x + std::get<0>(parentPos));
    }
}

std::tuple<int, int> Window::getPosition(void)
{
    // The globel position of the window
    auto globalPos = getGlobalPos();

    auto parentGlobalPos = this->getParent()->getGlobalPos();

    int relx, rely;
    relx = std::get<0>(globalPos) - std::get<0>(parentGlobalPos);
    rely = std::get<1>(globalPos) - std::get<1>(parentGlobalPos);

    return std::make_tuple(relx, rely);
}

Drawable *Window::getParent(void) { return this->parent; }

void Window::redraw(void)
{
    int xPos = 0, yPos = 0;
    assert(this->thisWin);
    if (this->thisWin)
    {
        getyx(this->thisWin, yPos, xPos);
        delwin(this->thisWin);
        this->thisWin = nullptr;
    }

    this->thisWin = newwin(this->ywid, this->xwid, yPos, xPos);
    box(this->thisWin, 0, 0);
}

std::tuple<int, int> Window::getGlobalPos(void)
{
    assert(this->thisWin);
    if (this->thisWin)
    {
        int globx, globy;
        getyx(this->thisWin, globy, globx);

        return std::make_tuple(globx, globy);
    }
    else
    {
        // TODO: throw exception insted
        return std::make_tuple(-1, -1);
    }
}

void Window::dRefresh(void) { wrefresh(this->thisWin); }

void Window::setSize(int xSize, int ySize)
{
    assert(this->thisWin);
    if (this->thisWin)
    {
        this->xwid = xSize;
        this->ywid = ySize;

        wresize(this->thisWin, this->ywid, this->xwid);
        // TODO: this is just until we have the refreshAboveElements function
        this->dRefresh();
    }
}

} // namespace Elements

/* IMPLEMENTATION OF WINDOWHANDLER */

WindowHandler *WindowHandler::masterWindowHandler = nullptr;

WindowHandler::WindowHandler(void) : childGuiElements()
{
    /* TODO: find the function to not set a blocking timer after a 'function
     * key is pressed' */

    initscr();
    // send keys as they are pressed
    cbreak();
    noecho();
    // wait 1 tenths of a ms everytime getch is called
    halfdelay(1);

    // TODO: this should be only enabled on the playwindow when we make it
    // enable arrow keys on stdscr
    keypad(stdscr, TRUE);

    /* SETUP WINDOWS AND ATTRIBUTES */
    updatexywid();
    redraw();

    // Because it's a singleton
    this->masterWindowHandler = this;
}

WindowHandler::~WindowHandler(void)
{
    // we need to delete all ncurses elements before we call endwin
    this->childGuiElements.clear();
    this->playAreaWindow = nullptr;
    endwin();
}

bool WindowHandler::updatexywid(void)
{
    int oldx = this->xwid, oldy = this->ywid;
    bool changed = false;
    getmaxyx(stdscr, ywid, xwid);
    if ((oldx != this->xwid) || (oldy != this->ywid))
    {
        changed = true;
    }

    return changed;
}

void WindowHandler::redraw(void)
{
    erase();

    // If the play area window has yet to be initialized
    if (this->playAreaWindow == nullptr)
    {
        this->playAreaWindow =
            new Elements::Window(this, this->xwid, this->ywid - 1, 0, 0);
        this->childGuiElements.push_back(this->playAreaWindow);
    }
    else
    {
        this->playAreaWindow->setSize(this->xwid, this->ywid - 1);
    }

    // Breth first to retain depth
    // TODO: Write breth first alg in InterfaceElement

    // TODO: this is just for whilst we dont have the above mentioned algorithem
    for (auto *element : this->childGuiElements)
    {
        element->redraw();
    }

    // TODO: this is just for testing
    this->playAreaWindow->setText(0, 0, "Hello");
}

void WindowHandler::setText(int x, int y, std::string str)
{
    mvprintw(y, x, str.c_str());
}

std::tuple<int, int> WindowHandler::getGlobalPos(void)
{
    return std::make_tuple(0, 0);
}

void WindowHandler::dRefresh(void)
{
    handleKeyEvent(getch());

    /* TODO: This is just while were testing, eventually we should do something
     * else when the screen is resized */
    if (updatexywid())
    {
        redraw();
    }

    mvprintw((ywid - 1), 0, "paused wid:%d, height:%d", xwid, ywid);
    // ncurses refresh
    refresh();

    if (this->playAreaWindow != nullptr)
    {
        this->playAreaWindow->setPosition(0, 0);

        // TODO: While we don't have the breth first alg in InterfaceElement
        this->playAreaWindow->dRefresh();
    }
}

void WindowHandler::handleKeyEvent(int toHandle)
{
    switch (toHandle)
    {
    // The escape key
    case 'P':
        this->engineInterfaceController->sendMessage(
            Message{.type = PAUSE, .state = nullptr});
        break;
    case 'Q':
        // TODO: this is just while we develop the rest of the system
        assert(this->engineInterfaceController);
        if (this->engineInterfaceController)
        {
            printw("KeyPressed %d", toHandle);
            this->engineInterfaceController->sendMessage(
                Message{.type = STOP, .state = nullptr});
        }
        break;
    default:
        // TODO: this is just for testing
        // 21 is the current length of our window size info message
        mvprintw(this->ywid - 1, (21 + 6), "The %c key was pressed.",
                 static_cast<char>(toHandle));
        break;
    }
}

void WindowHandler::openPausedWindow(void)
{
    // TODO: display the paused window
    // TODO: this is just for testing and wist the depth first alg in window dne
    this->playAreaWindow->setText(0, 0, "Paused");
    this->playAreaWindow->dRefresh();
}

void WindowHandler::pause(void)
{
    this->running = false;
    this->openPausedWindow();
}

std::tuple<int, int> WindowHandler::getPlayAreaDimen(void) const
{
    // TODO: make this actuall equate to how it will work
    return std::make_tuple(0, 0);
}

WindowHandler *WindowHandler::getWindowHandlerSingleton(void)
{
    if (WindowHandler::masterWindowHandler == nullptr)
        WindowHandler::masterWindowHandler = new WindowHandler();
    return WindowHandler::masterWindowHandler;
}

/* SnecObserver Implementation */
void WindowHandler::sendMessage(SnecMessage message)
{
    switch (message.type)
    {
    case PAUSE:
        this->pause();
        break;
    case UPDATE:
        this->dRefresh();
        break;
    // TODO: fill in what happends here
    case STATEINFO:
    case INTERFACEINFO:
    case STOP:
        break;
    }
}

void WindowHandler::linkObservable(SnecObservable *ovservable)
{
    if (ovservable)
    {
        this->engineInterfaceController = ovservable;
    }
}

void WindowHandler::unlinkObservable(void)
{
    if (this->engineInterfaceController)
    {
        this->engineInterfaceController = nullptr;
    }
}

} // namespace View
