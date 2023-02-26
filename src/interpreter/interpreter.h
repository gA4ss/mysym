#ifndef MYSYM_INTERPRETER_INTERPRETER_H_
#define MYSYM_INTERPRETER_INTERPRETER_H_

#include <mysym/mysym.h>

namespace mysym
{
  namespace interpreter
  {
    symbol_t interpret(std::string s);
  } // namespace interpreter
} // namespace mysym

#endif