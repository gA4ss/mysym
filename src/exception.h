#ifndef MYSYM_EXCEPTION_H_
#define MYSYM_EXCEPTION_H_

#include <my/my_exception.h>

namespace mysym
{

#define mysym_exception(format, ...)                                              \
  {                                                                               \
    throw my::MyException("<mysym>",                                              \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mysym_invalid_param_type_exception(format, ...)                           \
  {                                                                               \
    throw my::MyException("<mysym> invalid param type",                           \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mysym_opt_not_operator_exception(format, ...)                             \
  {                                                                               \
    throw my::MyException("<mysym> opt is not operator",                          \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mysym_invalid_symbol_format_exception(format, ...)                        \
  {                                                                               \
    throw my::MyException("<mysym> invalid symbol format",                        \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mysym_not_found_operator_exception(format, ...)                           \
  {                                                                               \
    throw my::MyException("<mysym> can't found operator",                         \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mysym_param_is_out_of_range_exception(format, ...)                        \
  {                                                                               \
    throw my::MyException("<mysym> param is out of the range",                    \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mysym_assert(exp, format, ...) my_assert(exp, format, __VA_ARGS__)

  //////////////////////////////
  //  定义了一些常用参数检查宏   //
  //////////////////////////////

#define check_param_type(s, ty)                                                                                                         \
  {                                                                                                                                     \
    if (kind(s) != (ty))                                                                                                                \
    {                                                                                                                                   \
      mysym_invalid_param_type_exception("\'%s\' must be \'%s\' type, it's %s.", (s).literal.c_str(), opt_name(ty).c_str(), opt_name(kind(s)).c_str()); \
    }                                                                                                                                   \
  }

#define check_list_all_variate_type(ps)                                                                                            \
  {                                                                                                                                \
    for (auto it = (ps).begin(); it != (ps).end(); it++)                                                                           \
    {                                                                                                                              \
      if (!is_var(kind(*it)))                                                                                                      \
      {                                                                                                                            \
        mysym_invalid_param_type_exception("\'%s\' must be variate type, it's \'%s\'.", it->literal.c_str(), opt_name(kind(*it)).c_str()); \
      }                                                                                                                            \
    }                                                                                                                              \
  }

} // namespace mysym

#endif // MYSYM_EXCEPTION_H_