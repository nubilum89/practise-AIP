#ifndef PLOT_HPP
#define PLOT_HPP
#include <cstddef>
#include "ints.hpp"
#include "point.hpp"
#include "points.hpp"

class Plot
{
public:
  void set(int x, int y);
  int calc(int x) const;
  size_t solve(Ints & buf, int y) const;
  Points append(p_t p) const;
private:
  Ints data_;
};

#endif
