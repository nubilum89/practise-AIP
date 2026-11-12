#ifndef MTX_HPP
#define MTX_HPP
#include <cstddef>
#include "ints.hpp"

class Mtx
{
public:
  Mtx();
  Mtx(size_t m, size_t n);
  ~Mtx() = default;
  void set(size_t i, size_t j, int value);
  int get(size_t i, size_t j) const;
  Mtx sum(const Mtx & oth) const;
  Mtx mul(const Mtx & oth) const;
  Mtx transpose() const;
  int det() const;
  Mtx add_row(int init) const;
  Ints getCol(size_t id) const;
  Ints getRow(size_t id) const;
private:
  Mtx getMinor(size_t row, size_t col) const;
  size_t m;
  size_t n;
  Ints data;
};

#endif
