#include <iostream>
#include <regex>
using namespace std;

int main()
{
  string str = "sigalhu233";

  regex r("[a-z0-9]+");
  cout << "正则表达式：[a-z0-9]+" << endl;
  if (regex_match(str, r))
    cout << "字符串：" << str << " 匹配成功！" << endl;
  else
    cout << "字符串：" << str << " 匹配失败！" << endl;

  cout << endl
       << "正则表达式：\\d+" << endl;
  if (regex_match(str, regex("\\d+")))
    cout << "字符串：" << str << " 匹配成功！" << endl;
  else
    cout << "字符串：" << str << " 匹配失败！" << endl;

  cout << endl
       << "正则表达式：\\d+" << endl;
  if (regex_match(str.begin() + 7, str.end(), regex("\\d+")))
    cout << "字符串：" << &str[7] << " 匹配成功！" << endl;
  else
    cout << "字符串：" << &str[7] << " 匹配失败！" << endl;

  smatch sm;
  cout << endl
       << "正则表达式：([a-z]+)(\\d+)" << endl;
  if (regex_match(str.cbegin() + 5, str.cend(), sm, regex("([a-z]+)(\\d+)")))
  {
    cout << "字符串：" << &str[5] << " 匹配成功！" << endl;
    cout << "匹配字符串个数：" << sm.size() << endl;
    cout << "分别为：";
    for (auto aa : sm)
      cout << aa.str() << " ";
    cout << endl;
  }
  else
    cout << "字符串：" << &str[5] << " 匹配失败！" << endl;

  cmatch cm;
  cout << endl
       << "正则表达式：([a-z]+)(\\d+)" << endl;
  if (regex_match(str.c_str(), cm, regex("([a-z]+)(\\d+)")))
  {
    cout << "字符串：" << str << " 匹配成功！" << endl;
    cout << "匹配字符串个数：" << cm.size() << endl;
    cout << "分别为：";
    for (auto aa : cm)
      cout << aa.str() << " ";
    cout << endl;
  }
  else
    cout << "字符串：" << str << " 匹配失败！" << endl;
  return 0;
}