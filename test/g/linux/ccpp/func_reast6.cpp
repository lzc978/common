/**
 * C++函数重载
 * 在实际开发中，有时候我们需要实现几个功能类似的函数，只是有些细节不同。例如希望交换两个变量的值，这两个变量有多种类型，可以是 int、float、char、bool 等，我们需要通过参数把变量的地址传入函数内部。在C语言中，程序员往往需要分别设计出三个不同名的函数，其函数原型与下面类似：
 * \code
 * void swap1(int *a, int *b);      //交换 int 变量的值
 * void swap2(float *a, float *b);  //交换 float 变量的值
 * void swap3(char *a, char *b);    //交换 char 变量的值
 * void swap4(bool *a, bool *b);    //交换 bool 变量的值
 * \endcode
 */
//但在C++中，这完全没有必要。C++ 允许多个函数拥有相同的名字，只要它们的参数列表不同就可以，这就是函数的重载（Function Overloading）。借助重载，一个函数名可以有多种用途。
//参数列表又叫参数签名，包括参数的类型、参数的个数和参数的顺序，只要有一个不同就叫做参数列表不同。

//注意，参数列表不同包括参数的个数不同、类型不同或顺序不同，仅仅参数名称不同是不可以的。函数返回值也不能作为重载的依据。
/*
函数的重载的规则：
    函数名称必须相同。
    参数列表必须不同（个数不同、类型不同、参数排列顺序不同等）。
    函数的返回类型可以相同也可以不相同。
    仅仅返回类型不同不足以成为函数的重载。
*/

#include <iostream>
using namespace std;
//交换 int 变量的值
void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//交换 float 变量的值
void Swap(float *a, float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}
//交换 char 变量的值
void Swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
//交换 bool 变量的值
void Swap(bool *a, bool *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    //交换 int 变量的值
    int n1 = 100, n2 = 200;
    Swap(&n1, &n2);
    cout<<n1<<", "<<n2<<endl;
   
    //交换 float 变量的值
    float f1 = 12.5, f2 = 56.93;
    Swap(&f1, &f2);
    cout<<f1<<", "<<f2<<endl;
   
    //交换 char 变量的值
    char c1 = 'A', c2 = 'B';
    Swap(&c1, &c2);
    cout<<c1<<", "<<c2<<endl;
   
    //交换 bool 变量的值
    bool b1 = false, b2 = true;
    Swap(&b1, &b2);
    cout<<b1<<", "<<b2<<endl;
    return 0;
}
