#ifndef INTS_HPP
#define INTS_HPP
#include <cstddef>

class Ints
{
public:
  Ints();
  Ints(size_t size, int value);
  Ints(const Ints & rhs);
  Ints(Ints && rhs) noexcept;
  Ints & operator=(const Ints & rhs);
  Ints & operator=(Ints && rhs) noexcept;
  Ints operator+(const Ints & rhs) const;
  ~Ints();

  size_t getSize() const noexcept;
  void set(size_t id, int i) noexcept;
  int get(size_t id) const noexcept;
  void setSafe(size_t id, int i);
  int getSafe(size_t id) const;

  Ints append(int i) const;
  Ints append(Ints b) const;

  static Ints unitializatedInts(size_t size);

private:
  void resize();
  size_t capacity_;
  size_t size_;
  int * data_;
};

#endif
