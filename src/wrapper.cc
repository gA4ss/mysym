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

mysym::symbol_t operator+(const mysym::symbol_t &x, std::string y)
{
  return mysym::add(x, mysym::create_symbol(y));
}

mysym::symbol_t operator-(const mysym::symbol_t &x, std::string y)
{
  return mysym::sub(x, mysym::create_symbol(y));
}

mysym::symbol_t operator*(const mysym::symbol_t &x, std::string y)
{
  return mysym::mul(x, mysym::create_symbol(y));
}

mysym::symbol_t operator/(const mysym::symbol_t &x, std::string y)
{
  return mysym::div(x, mysym::create_symbol(y));
}

mysym::symbol_t operator%(const mysym::symbol_t &x, std::string y)
{
  return mysym::mod(x, mysym::create_symbol(y));
}

mysym::symbol_t operator+(std::string x, const mysym::symbol_t &y)
{
  return mysym::add(mysym::create_symbol(x), y);
}

mysym::symbol_t operator-(std::string x, const mysym::symbol_t &y)
{
  return mysym::sub(mysym::create_symbol(x), y);
}

mysym::symbol_t operator*(std::string x, const mysym::symbol_t &y)
{
  return mysym::mul(mysym::create_symbol(x), y);
}

mysym::symbol_t operator/(std::string x, const mysym::symbol_t &y)
{
  return mysym::div(mysym::create_symbol(x), y);
}

mysym::symbol_t operator%(std::string x, const mysym::symbol_t &y)
{
  return mysym::mod(mysym::create_symbol(x), y);
}

mysym::symbol_t operator+(const mysym::symbol_t &x, mysym::real_t y)
{
  return mysym::add(x, mysym::create_symbol(std::to_string(y)));
}

mysym::symbol_t operator-(const mysym::symbol_t &x, mysym::real_t y)
{
  return mysym::sub(x, mysym::create_symbol(std::to_string(y)));
}

mysym::symbol_t operator*(const mysym::symbol_t &x, mysym::real_t y)
{
  return mysym::mul(x, mysym::create_symbol(std::to_string(y)));
}

mysym::symbol_t operator/(const mysym::symbol_t &x, mysym::real_t y)
{
  return mysym::div(x, mysym::create_symbol(std::to_string(y)));
}

mysym::symbol_t operator%(const mysym::symbol_t &x, mysym::real_t y)
{
  return mysym::mod(x, mysym::create_symbol(std::to_string(y)));
}

mysym::symbol_t operator+(mysym::real_t x, const mysym::symbol_t &y)
{
  return mysym::add(mysym::create_symbol(std::to_string(x)), y);
}

mysym::symbol_t operator-(mysym::real_t x, const mysym::symbol_t &y)
{
  return mysym::sub(mysym::create_symbol(std::to_string(x)), y);
}

mysym::symbol_t operator*(mysym::real_t x, const mysym::symbol_t &y)
{
  return mysym::mul(mysym::create_symbol(std::to_string(x)), y);
}

mysym::symbol_t operator/(mysym::real_t x, const mysym::symbol_t &y)
{
  return mysym::div(mysym::create_symbol(std::to_string(x)), y);
}

mysym::symbol_t operator%(mysym::real_t x, const mysym::symbol_t &y)
{
  return mysym::mod(mysym::create_symbol(std::to_string(x)), y);
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

mysym::symbol_t operator~(const mysym::symbol_t &x)
{
  return mysym::mul(mysym::gConstNegOne, x);
}

mysym::symbol_t operator&(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return x;
}

mysym::symbol_t operator|(const mysym::symbol_t &x, const mysym::symbol_t &y)
{
  return x;
}

const mysym::symbol_t& operator>>(std::istream& in, mysym::symbol_t &x)
{
  std::string str;
  in >> str;
  x = mysym::create_symbol(str);
  return x;
}

std::ostream& operator<<(std::ostream& out, const mysym::symbol_t &x)
{
  out << mysym::print_string(x);
  return out;
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