#ifndef POINTS_HPP
#define POINTS_HPP
#include <cstddef>
#include "ints.hpp"
#include "point.hpp"

class Points
{
public:
  void set(size_t id, p_t p);
  p_t get(size_t id) const;
  Points append(p_t p) const;
  size_t getSize() const noexcept;
private:
  Ints data_;
};

#endif
