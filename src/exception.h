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

} // namespace mysym

#endif // MYSYM_EXCEPTION_H_