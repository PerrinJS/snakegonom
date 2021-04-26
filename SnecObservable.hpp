#pragma once

#include "SnecObserver.hpp"

class SnecObservable: public SnecObserver
{
public:
    virtual void attach(SnecObserver *observer) = 0;

private:
    //virtual void notifyAll(void) = 0;
};
