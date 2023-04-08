#include <mysym/mysym.h>

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

    mympf::float_t nf = mympf::create(numerator(s).literal);
    mympf::float_t df = mympf::create(denominator(s).literal);
    mympf::float_t rf = mympf::div(nf, df);
    return create_flt(mympf::print_string(rf));
  }

  symbol_t num_to_frac(const symbol_t &s)
  {
    if (kind(s) != kOptNumber)
      return s;

    mympf::float_t c = mympf::create(s.literal);
    mynum::fraction_t f = mynum::f::fraction(c);
    return c_frac(mympz::print_string(f.first), mympz::print_string(f.second));
  }

  mynum::fraction_t frac_to_mynum_fraction(const symbol_t &s)
  {
    mynum::fraction_t f;
    f.first = mympz::create(numerator(s).literal);
    f.first = mympz::create(denominator(s).literal);
    return f;
  }
} // namespace mysym