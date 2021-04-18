#pragma once

#include <vector>

#include "SnakeEngine.hpp"

class WindowHandler
{
public:
    WindowHandler(void);
    ~WindowHandler(void);

    void pause(void);
    std::vector<int> getPlayAreaDimen(void);
};
