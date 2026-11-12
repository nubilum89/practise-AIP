#include "plot.hpp"
#include <stdexcept>

void Plot::set(int x, int y)
{
  for (size_t i = 0; i < data_.getSize(); i+=2)
  {
    if (x == data_.get(i))
    {
      data_.set(i + 1, y);
      return;
    }
  }

  data_ = data_.append(x).append(y);
}

int Plot::calc(int x) const
{
  for (size_t i = 0; i < data_.getSize(); i+=2)
  {
    if (x == data_.get(i))
    {
      return data_.get(i + 1);
    }
  }

  throw std::logic_error("No such x");
}

size_t Plot::solve(Ints & buf, int y) const
{
  size_t cnt = 0;
  for (size_t i = 1; i < data_.getSize(); i+=2)
  {
    if (y == data_.get(i))
    {
      buf = buf.append(data_.get(i - 1));
      ++cnt;
    }
  }

  return cnt;
}

Points Plot::append(p_t p) const
{
  Points res;
  for (size_t i = 1; i < data_.getSize(); i+=2)
  {
    p_t cur = {data_.get(i - 1), data_.get(i)};
    res = res.append(cur);
  }

  return res.append(p);
}
