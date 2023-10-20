static symbol_t __sub_log_log(const symbol_t &x, const symbol_t &y)
{
  symbol_t xb = base(x), yb = base(y);
  symbol_t xe = exponent(x), ye = exponent(y);
  if (compare(xb, yb) == 0)
  {
    symbol_t z = create(kOptLog);
    append(z, xb);
    //
    // 这里需要判断y的符号是正还是负
    //
    symbol_t ze = div(xe, ye);
    // if (sign(ye) == kSignPositive)
    // {
    //   ze = div(xe, ye);
    // }
    // else
    // {
    //   ze = mul(xe, opposite(ye));
    // }
    append(z, ze);
    return z;
  }
  return just_make2(kOptSub, x, y);
}
