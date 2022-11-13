#ifndef MYSYM_DEBUG_H_
#define MYSYM_DEBUG_H_

#include <my/my_debug.h>

namespace mysym
{

#ifdef DEBUG
#define mysym_dbgprint(s) my::dbgprint(__FILE__, __LINE__, __FUNCTION__, "%s", (s))
#define mysym_dbgprint_fmt(format, ...) my::dbgprint(__FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__)
#else
#define mysym_dbgprint(s)
#define mysym_dbgprint_fmt(format, ...)
#endif

} // namespace mysym

#endif // MYSYM_DEBUG_H_