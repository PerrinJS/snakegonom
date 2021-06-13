#include "SnakeEngine.hpp"


SnakeEngine::SnakeEngine(int width, int height):
    m_snakeCreatedHere(true),
    m_playfieldCreatedHere(true),
    m_snake()
{
    this->m_playfield = new PlayField(boost::extents[width][height]);
}

SnakeEngine::SnakeEngine(int width, int height, Snake *snake):
    m_playfieldCreatedHere(true)
{
    this->m_playfield = new PlayField(boost::extents[width][height]);
    this->m_snake = snake;
}

SnakeEngine::SnakeEngine(Snake *snake, PlayField *playfield)
{
    this->m_playfield = playfield;
    this->m_snake = snake;
}

SnakeEngine::~SnakeEngine(void)
{
    if(this->m_playfieldCreatedHere)
        delete this->m_playfield;
    if(this->m_snakeCreatedHere)
        delete this->m_snake;
}

void SnakeEngine::pause(void)
{
    //TODO: This currently has no use other than consistency of interface
}

void SnakeEngine::seUpdate(void)
{
    //TODO
}

/* SnecObserver Implementation */
void SnakeEngine::sendMessage(SnecMessage message)
{
    switch(message.type)
    {
        //TODO: actually do something with this
        case UPDATE:
            this->seUpdate();
            break;
        case STATEINFO: break;
        case INTERFACEINFO: break;
        case PAUSE:
            this->pause();
            break;
    }
} 
