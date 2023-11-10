static symbol_t __add_log_log(const symbol_t &x, const symbol_t &y)
{
  symbol_t xb = base(x), yb = base(y);
  symbol_t xe = exponent(x), ye = exponent(y);
  if (compare(xb, yb) == 0)
  {
    symbol_t z = create(kOptLog);
    append(z, xb);
    symbol_t ze = mul(xe, ye);
    append(z, ze);
    return z;
  }
  return just_make2(kOptAdd, x, y);
}
