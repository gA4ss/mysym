#ifndef MYSYM_WRAPPER_H_
#define MYSYM_WRAPPER_H_

#include <mysym/mysym.h>

// 不可以重载的运算符		 .、.*、?：、::、: 和sizeof、typeid、cast(4种)

mysym::symbol_t operator+(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator-(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator*(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator/(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator%(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator++(mysym::symbol_t &x);
mysym::symbol_t operator--(mysym::symbol_t &x);
mysym::symbol_t operator++(mysym::symbol_t &x, int i);
mysym::symbol_t operator--(mysym::symbol_t &x, int i);

mysym::symbol_t operator&(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator|(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator~(const mysym::symbol_t &x);
mysym::symbol_t operator>>(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator<<(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator^(const mysym::symbol_t &x, const mysym::symbol_t &y);

bool operator||(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator&&(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator!(const mysym::symbol_t &x);

bool operator<(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator<=(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator>(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator>=(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator==(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator!=(const mysym::symbol_t &x, const mysym::symbol_t &y);

// void operator=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator+=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator-=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator*=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator/=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator%=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator&=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator|=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator^=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator<<=(mysym::symbol_t &x, const mysym::symbol_t &y);
void operator>>=(mysym::symbol_t &x, const mysym::symbol_t &y);

// 其他运算符	[]、()、->、逗号、new、delete、new[]、delete[]、->*

#endif // MYSYM_WRAPPER_H_