#include "ints.hpp"
#include <utility>
#include <cstddef>
#include <limits>
#include <stdexcept>

Ints::Ints():
  capacity_(0),
  size_(0),
  data_(nullptr)
{}

Ints::Ints(size_t size, int value):
  capacity_(size),
  size_(size),
  data_(new int [size])
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = value;
  }
}

Ints Ints::unitializatedInts(size_t size)
{
  Ints temp;
  temp.size_ = 0;
  temp.capacity_ = size;
  temp.data_ = new int [size];

  return temp;
}

Ints::Ints(const Ints & rhs):
  capacity_(rhs.capacity_),
  size_(rhs.size_),
  data_(new int [capacity_])
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

Ints::Ints(Ints && rhs) noexcept:
  capacity_(rhs.capacity_),
  size_(rhs.size_),
  data_(rhs.data_)
{
  rhs.capacity_ = 0;
  rhs.size_ = 0;
  rhs.data_ = nullptr;
}

Ints & Ints::operator=(const Ints & rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  Ints temp(rhs);

  std::swap(capacity_, temp.capacity_);
  std::swap(size_, temp.size_);
  std::swap(data_, temp.data_);

  return *this;
}

Ints & Ints::operator=(Ints && rhs) noexcept
{
  if (this != &rhs)
  {
    delete [] data_;

    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = rhs.data_;

    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
  }

  return *this;
}

Ints Ints::operator+(const Ints & rhs) const
{
  if (getSize() != rhs.getSize())
  {
    throw std::invalid_argument("Arrays have different size");
  }

  Ints result(getSize(), 0);
  for (size_t i = 0; i < getSize(); ++i)
  {
    int a = get(i);
    int b = rhs.get(i);
    if ((b > 0 && a > std::numeric_limits< int >::max() - b)
        || (b < 0 && a < std::numeric_limits< int >::min() - b))
    {
      throw std::invalid_argument("overflow");
    }

    result.set(i, a + b);
  }

  return result;
}

Ints::~Ints()
{
  delete [] data_;
}

size_t Ints::getSize() const noexcept
{
  return size_;
}

void Ints::set(size_t id, int i) noexcept
{
  data_[id] = i;
}

int Ints::get(size_t id) const noexcept
{
  return data_[id];
}

void Ints::setSafe(size_t id, int i)
{
  if (id >= size_)
  {
    throw std::logic_error("Invalid value");
  }

  set(id, i);
}

int Ints::getSafe(size_t id) const
{
  if (id >= size_)
  {
    throw std::logic_error("Invalid value");
  }

  return get(id);
}

void Ints::resize()
{
  size_t newCapacity = 1;
  if (capacity_ > 0)
  {
    if (capacity_ > std::numeric_limits< size_t >::max() / 2)
    {
      throw std::logic_error("Overflow");
    }

    newCapacity = capacity_ * 2;
  }

  int * newData = new int [newCapacity];
  for (size_t i = 0; i < size_; ++i)
  {
    newData[i] = data_[i];
  }

  delete [] data_;
  data_ = newData;
  capacity_ = newCapacity;
}

Ints Ints::append(int i) const
{
  Ints result(*this);

  if (result.capacity_ < result.size_ + 1)
  {
    result.resize();
  }

  result.data_[result.size_] = i;
  ++result.size_;

  return result;
}

Ints Ints::append(Ints b) const
{
  if (b.size_ > std::numeric_limits< size_t >::max() - size_)
  {
    throw std::logic_error("Overflow");
  }

  Ints result = unitializatedInts(size_ + b.size_);
  for (size_t i = 0; i < size_; ++i)
  {
    result.data_[i] = data_[i];
  }

  for (size_t i = 0; i < b.size_; ++i)
  {
    result.data_[size_ + i] = b.data_[i];
  }

  result.size_ = size_ + b.size_;

  return result;
}
