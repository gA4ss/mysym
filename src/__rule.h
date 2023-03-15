//
// 加法规则
//
bool __c_add_num_num(const symbol_t &x, const symbol_t &y);
bool __c_add_num_frac(const symbol_t &x, const symbol_t &y);
bool __c_add_num_nature(const symbol_t &x, const symbol_t &y);
bool __c_add_num_var(const symbol_t &x, const symbol_t &y);
bool __c_add_num_func(const symbol_t &x, const symbol_t &y);

bool __c_add_frac_frac(const symbol_t &x, const symbol_t &y);
bool __c_add_frac_nature(const symbol_t &x, const symbol_t &y);
bool __c_add_frac_var(const symbol_t &x, const symbol_t &y);
bool __c_add_frac_func(const symbol_t &x, const symbol_t &y);

bool __c_add_nature_nature(const symbol_t &x, const symbol_t &y);
bool __c_add_nature_var(const symbol_t &x, const symbol_t &y);
bool __c_add_nature_func(const symbol_t &x, const symbol_t &y);

bool __c_add_var_var(const symbol_t &x, const symbol_t &y);
bool __c_add_var_func(const symbol_t &x, const symbol_t &y);

bool __c_add_func_func(const symbol_t &x, const symbol_t &y);

bool __c_add(const symbol_t &x, const symbol_t &y);
bool __c_add(const symbol_t &x);

symbol_t __e_add(const symbol_t &x, const symbol_t &y);
symbol_t __e_add(const symbol_t &x);

symbol_t __e_add_num_num(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_num_frac(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_num_nature(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_num_var(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_num_func(const symbol_t &x, const symbol_t &y);

symbol_t __e_add_frac_frac(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_frac_nature(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_frac_var(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_frac_func(const symbol_t &x, const symbol_t &y);

symbol_t __e_add_nature_nature(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_nature_var(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_nature_func(const symbol_t &x, const symbol_t &y);

symbol_t __e_add_var_var(const symbol_t &x, const symbol_t &y);
symbol_t __e_add_var_func(const symbol_t &x, const symbol_t &y);

symbol_t __e_add_func_func(const symbol_t &x, const symbol_t &y);

symbol_t __e_add(const symbol_t &x, const symbol_t &y);
symbol_t __e_add(const symbol_t &x);

//
// 乘法规则
//