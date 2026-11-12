#include "ints.hpp"
#include "mtx.hpp"
#include "plot.hpp"

int main()
{
  Ints a(10, 67);
  Ints b(10, 69);
  Ints c = a + b + a + b + a;
}
