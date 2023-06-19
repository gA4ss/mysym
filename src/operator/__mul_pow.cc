static symbol_t __mul_pow_pow(const symbol_t &x, const symbol_t &y)
{
  symbol_t xb = base(x), yb = base(y);
  symbol_t xe = exponent(x), ye = exponent(y);
  if (compare(xb, yb) == 0)
  {
    symbol_t z = create(kOptPow);
    append(z, xb);
    symbol_t ze = add(xe, ye);
    append(z, ze);
    return z;
  }
  return just_make2(kOptMul, x, y);
}