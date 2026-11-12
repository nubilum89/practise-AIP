#include "mtx.hpp"
#include <limits>
#include <stdexcept>

namespace
{
  int safeAdd(int a, int b)
  {
    if ((b > 0 && a > std::numeric_limits< int >::max() - b)
        || (b < 0 && a < std::numeric_limits< int >::min() - b))
    {
      throw std::overflow_error("Overflow");
    }

    return a + b;
  }

  int safeMul(int a, int b)
  {
    if (a == 0 || b == 0)
    {
      return 0;
    }

    if (a == -1 && b == std::numeric_limits< int >::min())
    {
      throw std::overflow_error("Overflow");
    }

    if (b == -1 && a == std::numeric_limits< int >::min())
    {
      throw std::overflow_error("Overflow");
    }

    if (a > 0)
    {
      if (b > 0 && a > std::numeric_limits< int >::max() / b)
      {
        throw std::overflow_error("Overflow");
      }
      if (b < 0 && b < std::numeric_limits< int >::min() / a)
      {
        throw std::overflow_error("Overflow");
      }
    }
    else
    {
      if (b > 0 && a < std::numeric_limits< int >::min() / b)
      {
        throw std::overflow_error("Overflow");
      }
      if (b < 0 && a < std::numeric_limits< int >::max() / b)
      {
        throw std::overflow_error("Overflow");
      }
    }

    return a * b;
  }
}

Mtx::Mtx():
  m(0),
  n(0),
  data()
{}

Mtx::Mtx(size_t m, size_t n):
  m(m),
  n(n),
  data()
{
  if (n != 0 && m > std::numeric_limits< size_t >::max() / n)
  {
    throw std::overflow_error("Overflow");
  }

  data = Ints(m * n, 0);
}

void Mtx::set(size_t i, size_t j, int value)
{
  if (i >= m || j >= n)
  {
    throw std::out_of_range("Invalid index");
  }

  data.set(i * n + j, value);
}

int Mtx::get(size_t i, size_t j) const
{
  if (i >= m || j >= n)
  {
    throw std::out_of_range("Invalid index");
  }

  return data.get(i * n + j);
}

Mtx Mtx::sum(const Mtx & oth) const
{
  if (m != oth.m || n != oth.n)
  {
    throw std::invalid_argument("Matrices have different size");
  }

  Mtx res(m, n);
  res.data = data + oth.data;

  return res;
}

Ints Mtx::getCol(size_t id) const
{
  if (id >= n)
  {
    throw std::out_of_range("Invalid column index");
  }

  Ints res = Ints::unitializatedInts(m);
  for (size_t i = 0; i < m; ++i)
  {
    res = res.append(data.get(i * n + id));
  }

  return res;
}

Ints Mtx::getRow(size_t id) const
{
  if (id >= m)
  {
    throw std::out_of_range("Invalid row index");
  }

  Ints res = Ints::unitializatedInts(n);
  for (size_t i = 0; i < n; ++i)
  {
    res = res.append(data.get(id * n + i));
  }

  return res;
}

Mtx Mtx::mul(const Mtx & oth) const
{
  if (n != oth.m)
  {
    throw std::invalid_argument("Invalid matrices size");
  }

  Mtx res(m, oth.n);
  for (size_t i = 0; i < m; ++i)
  {
    Ints row = getRow(i);
    for (size_t j = 0; j < oth.n; ++j)
    {
      Ints col = oth.getCol(j);
      int sm = 0;
      for (size_t z = 0; z < n; ++z)
      {
        sm = safeAdd(sm, safeMul(row.get(z), col.get(z)));
      }

      res.data.set(i * oth.n + j, sm);
    }
  }

  return res;
}

Mtx Mtx::transpose() const
{
  Mtx res(n, m);
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      res.data.set(j * m + i, data.get(i * n + j));
    }
  }

  return res;
}

Mtx Mtx::getMinor(size_t row, size_t col) const
{
  if (m == 0 || n == 0 || row >= m || col >= n)
  {
    throw std::out_of_range("Invalid index");
  }

  Mtx res(m - 1, n - 1);
  size_t id = 0;
  for (size_t i = 0; i < m; ++i)
  {
    if (i == row)
    {
      continue;
    }

    for (size_t j = 0; j < n; ++j)
    {
      if (j == col)
      {
        continue;
      }

      res.data.set(id, data.get(i * n + j));
      ++id;
    }
  }

  return res;
}

int Mtx::det() const
{
  if (m != n)
  {
    throw std::logic_error("Matrix is not square");
  }

  if (m == 0)
  {
    return 1;
  }

  if (m == 1)
  {
    return data.get(0);
  }

  int res = 0;
  int sign = 1;
  for (size_t j = 0; j < n; ++j)
  {
    int term = safeMul(sign * data.get(j), getMinor(0, j).det());
    res = safeAdd(res, term);
    sign = -sign;
  }

  return res;
}

Mtx Mtx::add_row(int init) const
{
  if (m == std::numeric_limits< size_t >::max())
  {
    throw std::overflow_error("Overflow");
  }

  Mtx res;
  res.m = m + 1;
  res.n = n;
  res.data = data.append(Ints(n, init));

  return res;
}
