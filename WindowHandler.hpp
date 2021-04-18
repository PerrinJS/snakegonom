#pragma once

#include "SnakeEngine.hpp"

class WindowHandler
{
private:
    SnakeEngine* m_engine = nullptr;
    void init(int width, int height);
    void init();
public:
    WindowHandler();
    WindowHandler(SnakeEngine* engine);
    ~WindowHandler();
};
