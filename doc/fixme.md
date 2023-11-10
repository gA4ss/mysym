
## 需要优化的问题

### 分数转浮点计算消耗
在*operator/cmp.cc*中的*__cmp_const_const*函数设计分数运算时,如果是整型则会自动转换成浮点，但是需要首先转换成整型然后再浮点，这样重复进行了运算，同样在*fraction.cc*中也涉及这个问题在*frac_to_num*函数。这类问题搜索*mynum::integer_to_float*函数可以得到所有位置，基本都是涉及到了除法运算。