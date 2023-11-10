## 表达式构造

在本开发库中，没有加法与除法两种运算符号，内部运算逻辑是有，但是并无符号，例如减法将会转换成加上一个负数。除法将会转换为乘以一个负指数的指数函数。在构造函数中，通过*make*函数进行了转换。

```c++
if (is_sub(opt))
{
  symbol_t ns2 = create_opt(kOptMul);
  append(ns2, gConstNegOne);
  append(ns2, s2);
  u = create_opt(kOptAdd);
  append(u, s1);
  append(u, ns2);
}
else if (is_div(opt))
{
  symbol_t ds2 = create_opt(kOptPow);
  append(ds2, s2);
  append(ds2, gConstNegOne);
  u = create_opt(kOptMul);
  append(u, s1);
  append(u, ds2);
}
```
## 运算符的执行流程

## 运算律

## 符号运算符

## 符号运算符集合

## 运算的配对

## 对♾️的处理

## API接口

### 运算符号接口

|名称|说明|
|---|----|


### 辅助函数接口

|名称|说明|
|---|----|


### C++运算符重载

|名称|说明|
|---|----|