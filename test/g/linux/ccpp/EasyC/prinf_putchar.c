#include <stdio.h>

/*
printf输出字符串
putchar输出字符
*/

int main()
{
    int a = 100;
    printf("a = %d\n", a); // 格式化输出一个字符串
    printf("%p\n", &a); //%p输出变量a在内存中的地址编号

    char b = 'a';
    putchar(b); //putchar只有一个参数, 就是要输出的char

    char* c = "abc"; //定义字符串
    printf("\n%s\n", c); //%s输出字符串
}