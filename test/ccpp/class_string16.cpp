/**
 * C++ 大大增强了对字符串的支持，除了可以使用C风格的字符串，还可以使用内置的 string 类。string 类处理起字符串来会方便很多，完全可以代替C语言中的字符数组或字符串指针。
 * string 是 C++ 中常用的一个类，它非常重要，我们有必要在此单独讲解一下。
 * 使用 string 类需要包含头文件<string>，下面的例子介绍了几种定义 string 变量（对象）的方法：
 * \code
 * #include <iostream>
#include <string>
using namespace std;
int main(){
    string s1;
    string s2 = "c plus plus";
    string s3 = s2;
    string s4 (5, 's');
    return 0;
}
    \endcode
 * 二. 删除字符串
 * erase() 函数可以删除 string 中的一个子字符串。它的一种原型为：
 * c++提供的string各种方法，站不了解
 */

