#pragma once

#include <vector>

class SnakeEngine;

typedef enum MessageType
{
    UPDATE,
    STATEINFO,
    INTERFACEINFO,
    PAUSE /* so we can from the interface send a message to the controller to
           * pause all dependent processes */
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
    virtual void sendMessage(SnecMessage message) = 0;
    virtual ~SnecObserver() = default;
};
