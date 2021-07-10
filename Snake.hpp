#pragma once

namespace GEntity
{
class Snake
{
  private:
    int m_length;

  public:
    Snake() = default;
    ~Snake() = default;

    int getLength();
};
} // namespace GEntity
