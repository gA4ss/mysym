#ifndef MYSYM_WRAPPER_H_
#define MYSYM_WRAPPER_H_

#include <mysym/mysym.h>

mysym::symbol_t operator+(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator-(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator*(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator/(const mysym::symbol_t &x, const mysym::symbol_t &y);
mysym::symbol_t operator%(const mysym::symbol_t &x, const mysym::symbol_t &y);

bool operator||(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator&&(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator!(const mysym::symbol_t &x);

bool operator<(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator<=(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator>(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator>=(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator==(const mysym::symbol_t &x, const mysym::symbol_t &y);
bool operator!=(const mysym::symbol_t &x, const mysym::symbol_t &y);

#endif // MYSYM_WRAPPER_H_