#include "points.hpp"

void Points::set(size_t id, p_t p)
{
  data_.setSafe(id * 2, p.x);
  data_.setSafe(id * 2 + 1, p.y);
}

p_t Points::get(size_t id) const
{
  p_t res = {data_.getSafe(id * 2), data_.getSafe(id * 2 + 1)};

  return res;
}

Points Points::append(p_t p) const
{
  Points res;
  res.data_ = data_.append(p.x).append(p.y);

  return res;
}

size_t Points::getSize() const noexcept
{
  return data_.getSize() / 2;
}
