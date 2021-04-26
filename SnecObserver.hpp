#pragma once

class SnakeEngine;

typedef enum MessageType
{
    UPDATE,
    STATEINFO,
    INTERFACEINFO,
    PAUSE /* so we can from the interface send a message to the controller to
           * pause all dependent processes */
} SnecMessageType;

typedef struct Message
{
    const SnecMessageType type;
    const SnakeEngine *state;
    //TODO: fill in state holding for interface changes
} SnecMessage;

class SnecObserver
{
public:
    virtual void sendMessage(SnecMessage message) = 0;
    virtual ~SnecObserver() = default;
};
