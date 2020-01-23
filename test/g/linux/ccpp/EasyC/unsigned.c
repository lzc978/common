#include <stdio.h>

/*
有符号数：最高位为符号位, 0代表正数, 1代表负数, 会溢出
无符号数：无符号数不可能是负数, 当程序处理一个不可能出现负数的值, 通常使用无符号数, 这样可以增大数的表达最大值
无符号 unsigned (int|char|float...)
*/

int main()
{
    unsigned int a = 322324244; //定义无符号整型变量
    printf("%X\n", a); //大写16进制int

    return 0;
}
