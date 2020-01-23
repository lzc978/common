#include <stdio.h>

int main()
{
    int a;
    int b = sizeof(a); //sizeof得到指定值占用内存的大小, 单位：字节byte
    printf("b = %d\n", b);

    size_t c = sizeof(a); //size_t是unsigned int 属于无符号整数
    printf("c = %u\n", c); //用无符号方式输出c的值

    return 0; 
}
