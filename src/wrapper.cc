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

mysym::symbol_t operator++(mysym::symbol_t &x)
{
  return add(x, mysym::gConstOne);
}

mysym::symbol_t operator--(mysym::symbol_t &x)
{
  return sub(x, mysym::gConstOne);
}

mysym::symbol_t operator++(mysym::symbol_t &x, int i)
{
  mysym::symbol_t y = x;
  x = add(x, mysym::gConstOne);
  return y;
}

mysym::symbol_t operator--(mysym::symbol_t &x, int i)
{
  mysym::symbol_t y = x;
  x = sub(x, mysym::gConstOne);
  return y;
}

mysym::symbol_t operator&(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return x;
}

mysym::symbol_t operator|(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return x;
}

mysym::symbol_t operator~(const mysym::symbol_t &x)
{
  return x;
}

mysym::symbol_t operator>>(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return x;
}

mysym::symbol_t operator<<(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return x;
}

mysym::symbol_t operator^(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return mysym::pow(x, y);
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

void operator+=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  x = mysym::add(x, y);
  return;
}

void operator-=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  x = mysym::sub(x, y);
  return;
}

void operator*=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  x = mysym::mul(x, y);
  return;
}

void operator/=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  x = mysym::div(x, y);
  return;
}

void operator%=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  x = mysym::mod(x, y);
  return;
}

void operator&=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return;
}

void operator|=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return;
}

void operator^=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  x = mysym::pow(x, y);
  return;
}

void operator<<=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return;
}

void operator>>=(mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return;
}

// 其他运算符	[]、()、->、逗号、new、delete、new[]、delete[]、->*