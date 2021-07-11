#pragma once

#include <vector>

#include "SnecObserver.hpp"

class SnecObservable : public SnecObserver
{
  public:
    virtual ~SnecObservable(void) override = default;

    /* It's probably good practise to write a function that returns what
     * catagories a particualr class subscribes to such that when it does
     * subscibe it's defined in code */
    /* The catagories define the lists the the observer subscribes to. */
    virtual void
    attach(SnecObserver *observer,
           const std::vector<SnecListenerCatagorization> catagories) = 0;

  private:
    // virtual void notifyAll(void) = 0;
};
