#ifndef MYSYM_OPERATOR_TEST_H_
#define MYSYM_OPERATOR_TEST_H_

namespace mysym
{

#define __test_opt(opt, x) (opt == kind(x))

#define __test_or(is_xxx, x, y) (is_xxx(kind(x)) || is_xxx(kind(y)))

#define __test_and(is_xxx, x, y) (is_xxx(kind(x)) && is_xxx(kind(y)))

#define __test_and_or(is_xxx, is_yyy, x, y) ((is_xxx(kind(x)) && is_yyy(kind(y))) || \
                                             (is_yyy(kind(y)) && is_xxx(kind(x))))

} // namespace mysym

#endif // MYSYM_OPERATOR_TEST_H_