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

#define mysym_symbol_name_already_exist_exception(name)                    \
  {                                                                        \
    throw my::MyException("<mysym> symbol name already exist",             \
                          __FILE__, __LINE__, __FUNCTION__, "%s", (name)); \
  }

#define mysym_invalid_range_in_params_exception(format, ...)                      \
  {                                                                               \
    throw my::MyException("<mysym> invalid range in params",                      \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

} // namespace mysym

#endif // MYSYM_EXCEPTION_H_