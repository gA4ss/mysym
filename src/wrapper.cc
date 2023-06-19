#include <mysym/wrapper.h>

mysym::symbol_t operator+(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return mysym::add(x, y);
}

mysym::symbol_t operator-(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return mysym::sub(x, y);
}

mysym::symbol_t operator*(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return mysym::mul(x, y);
}

mysym::symbol_t operator/(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return mysym::div(x, y);
}

mysym::symbol_t operator%(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return mysym::mod(x, y);
}

#define is_defined(s)       (kind(s) != kOptNone)

bool operator||(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return (is_defined(x) || is_defined(y));
}

bool operator&&(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return (is_defined(x) && is_defined(y));
}

bool operator!(const mysym::symbol_t &x)
{
  return !is_defined(x);
}

bool operator<(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return (mysym::compare(x, y) == -1);
}

bool operator<=(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return ((mysym::compare(x, y) == -1) || (mysym::compare(x, y) == 0));
}

bool operator>(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return (mysym::compare(x, y) == 1);
}

bool operator>=(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return ((mysym::compare(x, y) == 1) || (mysym::compare(x, y) == 0));
}

bool operator==(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return (mysym::compare(x, y) == 0);
}

bool operator!=(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return (mysym::compare(x, y) != 0);
}