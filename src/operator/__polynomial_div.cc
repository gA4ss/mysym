static bool __polynomial_div_const_const(const symbol_t &x, const symbol_t &y,
                                         symbol_t &n, symbol_t &d)
{
  bool r = false;
  if (is_num(kind(x)) && is_num(kind(y)))
  {
  }
  else if (is_frac(kind(x)) && is_frac(kind(y)))
  {
  }
  else if (is_num(kind(x)) && is_frac(kind(y)))
  {
  }
  else if (is_frac(kind(x)) && is_num(kind(y)))
  {
  }
  return r;
}

static bool __polynomial_div_sym_sym(const symbol_t &x, const symbol_t &y,
                                     symbol_t &n, symbol_t &d)
{
  bool r = false;
  symbol_t xb = base(x), yb = base(y);
  symbol_t xe = exponent(x), ye = exponent(y);
  if (compare(xb, yb) == 0)
  {
    if (compare(xe, ye) < 0)
    {
      ye = sub(ye, xe);
      n = gConstOne;
      d = pow(yb, ye);
    }
    else if (compare(xe, yb) > 0)
    {
      xe = sub(xe, ye);
      d = gConstOne;
      n = pow(xb, xe);
    }
    else
    {
      n = gConstOne;
      d = gConstOne;
    }
    r = true;
  }
  else if ((__test_and(is_num, x, y)) ||
           (__test_and(is_frac, x, y)) ||
           (__test_and_or(is_num, is_frac, x, y)))
  {
    r = __polynomial_div_const_const(x, y, n, d);
  }
  else
  {
    n = x;
    d = y;
    r = false;
  }
  return r;
}

static bool __polynomial_div_sym_mul(const symbol_t &x, const symbol_t &y,
                                     symbol_t &n, symbol_t &d)
{
  // 如果是单个符号也可以处理
  if (is_sym(kind(y)))
  {
    return __polynomial_div_sym_sym(x, y, n, d);
  }

  size_t ny = size(y);
  for (size_t i = 0; i < ny; i++)
  {
    if (__polynomial_div_sym_sym(x, y[i], n, d) == true)
    {
      if (compare(d, gConstOne) == 0)
      {
        d = y;
        erase(d, i);
      }
      else
      {
        symbol_t _y = y;
        _y.items[i] = d;
        d = _y;
      }
      return true;
    }
  } /* end for */
  n = x;
  d = y;
  return false;
}

static bool __polynomial_div_mul_sym(const symbol_t &x, const symbol_t &y,
                                     symbol_t &n, symbol_t &d)
{
  // 如果是单个符号也可以处理
  if (is_sym(kind(x)))
  {
    return __polynomial_div_sym_sym(x, y, n, d);
  }

  symbol_t z;
  size_t nx = size(x);
  for (size_t i = 0; i < nx; i++)
  {
    if (__polynomial_div_sym_sym(x[i], y, n, d) == true)
    {
      if (compare(n, d) == 0) // n = d = 1
      {
        n = x;
        erase(n, i);
      }
      else if (compare(n, gConstOne) == 0)
      {
        n = x;
        erase(n, i);
      }
      else if (compare(d, gConstOne) == 0)
      {
        symbol_t _x = x;
        _x.items[i] = n;
        n = _x;
      }
      return true;
    }
  } /* end for */
  n = x;
  d = y;
  return false;
}

static bool __polynomial_div_sym_add(const symbol_t &x, const symbol_t &y,
                                     symbol_t &n, symbol_t &d)
{
  symbol_t l;
  symbol_t g = gcd(y, l);
  if (compare(g, gConstOne) == 0)
  {
    n = x;
    d = y;
    return false;
  }

  symbol_t _n, _d;
  if (!__polynomial_div_sym_mul(x, g, _n, _d))
  {
    n = x;
    d = y;
    return false;
  }

  n = _n;
  d = mul(_d, l);
  return true;
}

static bool __polynomial_div_add_sym(const symbol_t &x, const symbol_t &y,
                                     symbol_t &n, symbol_t &d)
{
  symbol_t l;
  symbol_t g = gcd(x, l);
  if (compare(g, gConstOne) == 0)
  {
    n = x;
    d = y;
    return false;
  }

  symbol_t _n, _d;
  if (!__polynomial_div_sym_mul(g, y, _n, _d))
  {
    n = x;
    d = y;
    return false;
  }

  n = mul(_n, l);
  d = _d;
  return true;
}

static bool __polynomial_div_mul_mul(const symbol_t &x, const symbol_t &y,
                                     symbol_t &n, symbol_t &d)
{
  // symbol_t nc = constant(x), dc = constant(y);
  // symbol_t nt = term(x), dt = term(y);
  // symbol_t gc = gcd(nc, dc);
  // symbol_t gt = gcd(x, y);
  return true;
}

static inline symbol_t __polynomial_div(const symbol_t &x, const symbol_t &y)
{
  symbol_t z;
  return z;
}