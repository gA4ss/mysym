#include <mysym/mysym.h>

namespace mysym
{
  symbol_ptr_t make(opt_t opt, symbol_ptr_t s)
  {
    symbol_ptr_t o_ptr = create(opt);
    o_ptr->link(s);
    return o_ptr;
  }

  symbol_ptr_t make(opt_t opt, symbol_ptr_t s1, symbol_ptr_t s2)
  {
    symbol_ptr_t o_ptr = create(opt);
    o_ptr->link(s1);
    o_ptr->link(s2);
    return o_ptr;
  }

  symbol_ptr_t make_(opt_t opt, std::string s)
  {
    symbol_ptr_t o_ptr = create(opt);
    symbol_ptr_t s_ptr = create(kOptVar, s);

    o_ptr->link(s_ptr);
    return o_ptr;
  }

  symbol_ptr_t make_(opt_t opt, std::string s1, std::string s2)
  {
    symbol_ptr_t o_ptr = create(opt);
    symbol_ptr_t s1_ptr = create(kOptVar, s1);
    symbol_ptr_t s2_ptr = create(kOptVar, s2);

    o_ptr->link(s1_ptr);
    o_ptr->link(s2_ptr);
    return o_ptr;
  }

  symbol_ptr_t func(std::string fn, std::vector<symbol_ptr_t> args)
  {
    symbol_ptr_t f_ptr = create(kOptFunc, fn);
    f_ptr->next = args;
    return f_ptr;
  }

  symbol_ptr_t func_(std::string fn, std::vector<std::string> args)
  {
    symbol_ptr_t f_ptr = create(kOptFunc, fn);
    for (size_t i = 0; i < args.size(); i++)
    {
      f_ptr->link(create_var(args[i]));
    }

    return f_ptr;
  }
} // namespace mysym