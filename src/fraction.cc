#include <mysym/mysym.h>
#include <mynum/wrapper.h>

namespace mysym
{
  symbol_t numerator(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
      return s;
    return s.items[0];
  }

  symbol_t denominator(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
    {
      return create_int("1");
    }
    return s.items[1];
  }

  symbol_t frac_to_prod(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
      return s;

    symbol_t p = c_frac(create_int("1"), denominator(s));
    symbol_t u = c_mul(p, numerator(s));
    return u;
  }

  symbol_t frac_to_num(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
      return s;

    number_t nf = number_t(numerator(s).literal);
    number_t df = number_t(denominator(s).literal);
    number_t rf = nf / df;
    return create_flt(rf.value());
  }

  symbol_t num_to_frac(const symbol_t &s)
  {
    if (kind(s) != kOptNumber)
      return undefined;

    mympf::float_t c = mympf::create(s.literal);
    mynum::fraction_t f = mynum::f::fraction(c);
    return c_frac(mympz::print_string(f.first), mympz::print_string(f.second));
  }

  mynum::fraction_t frac_to_mynum_fraction(const symbol_t &s)
  {
    mynum::fraction_t f;
    f.first = mympz::create(numerator(s).literal);
    f.second = mympz::create(denominator(s).literal);
    return f;
  }

  symbol_t mynum_fraction_to_frac(const mynum::fraction_t &f)
  {
    return c_frac(mympz::print_string(f.first), mympz::print_string(f.second));
  }

  symbol_t compute_frac_num(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    mynum::fraction_t f1, f2;
    if (is_frac(kind(x)))
    {
      if (my::is_real(y.literal))
      {
        if (plibrary()->config.is_compute_frac_float)
          f2 = frac_to_mynum_fraction(num_to_frac(y));
        else
          return just_make2(opt, x, y);
      }
      else
      {
        f2 = frac_to_mynum_fraction(num_to_frac(y));
      }
      f1 = frac_to_mynum_fraction(x);
    }
    else
    {
      if (my::is_real(x.literal))
      {
        if (plibrary()->config.is_compute_frac_float)
          f2 = frac_to_mynum_fraction(num_to_frac(x));
        else
          return just_make2(opt, x, y);
      }
      else
      {
        f2 = frac_to_mynum_fraction(num_to_frac(x));
      }
      f1 = frac_to_mynum_fraction(y);
    }

    // 计算
    if (is_add(opt))
      return mynum_fraction_to_frac(mynum::f::add(f1, f2));
    else if (is_sub(opt))
      return mynum_fraction_to_frac(mynum::f::sub(f1, f2));
    else if (is_mul(opt))
      return mynum_fraction_to_frac(mynum::f::mul(f1, f2));
    else if (is_div(opt))
      return mynum_fraction_to_frac(mynum::f::div(f1, f2));
    return just_make2(opt, mynum_fraction_to_frac(f1), mynum_fraction_to_frac(f2));
  }

  symbol_t compute_frac_frac(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    mynum::fraction_t f1 = frac_to_mynum_fraction(x);
    mynum::fraction_t f2 = frac_to_mynum_fraction(y);
    mynum::fraction_t f3;
    if (is_add(opt))
      f3 = mynum::f::add(f1, f2);
    else if (is_sub(opt))
      f3 = mynum::f::sub(f1, f2);
    else if (is_mul(opt))
      f3 = mynum::f::mul(f1, f2);
    else if (is_div(opt))
      f3 = mynum::f::div(f1, f2);
    else
      return just_make2(opt, x, y);
    return mynum_fraction_to_frac(f3);
  }
} // namespace mysym