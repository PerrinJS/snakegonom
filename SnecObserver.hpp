#pragma once

#include <vector>

class SnakeEngine;
class SnecObservable;

typedef enum MessageType
{
    UPDATE,
    STATEINFO,
    INTERFACEINFO,
    PAUSE, /* so we can from the interface send a message to the controller to
            * pause all dependent processes */
    STOP
} SnecMessageType;

/* This is used to diferentiate what type of listener is subscribing and where
 * messages are sent.
 * i.e. if we have messages that we don't want to go to all components we
 * can sent the message to someting other than the system catagory */
typedef enum ListenerCatagorization
{
    ALL,
    SYSTEM // just the engine components
} SnecListenerCatagorization;

typedef struct Message
{
    const SnecMessageType type;
    const std::vector<SnecListenerCatagorization> catagory;
    const SnakeEngine *state;
    // TODO: fill in state holding for interface changes
} SnecMessage;

class SnecObserver
{
  public:
    /* only classes that need to send messages to the observable should
     * implement this */
    virtual void linkObservable(SnecObservable *) {}
    // to be called by the observable in the destructor
    // TODO: this is causing issues
    virtual void unlinkObservable(void) {}
    virtual void sendMessage(SnecMessage message) = 0;
    virtual ~SnecObserver(void) = default;
};
