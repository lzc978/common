#include <stdio.h>

//隐式转换，由编译器完成

/*
int main()
{
    int num = 5;
    printf("s1 = %d\n", num/2);
    printf("s2 = %lf\n", num/2.0);
    return 0;
}
*/

// 强制转换
// 强制类型转换是指的使用强制类型转换运算符，将一个变量或表达式转化成所需的类型

int main()
{
    float x = 0;
    int i = 0;
    x = 3.6f;
    i = x;// x 为实型浮点型，i为整型，直接赋值会有警告
    i = (int)x;//使用强制类型转换
    printf("x = %f, i = %d\n", x, i);
    return 0;
}