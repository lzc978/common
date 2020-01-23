#include <stdio.h>

/*
%d有符号10进制
%u无符号10进制
%o8进制int
%x16进制int, 字母小写
%X16进制int, 字母大写
*/
int main()
{
    int a = 123; //10进制
    int b = 0567; //8进制 前面加0代表8进制
    int c = 0xabc; //16进制 前面0x代表16进制

    printf("a = %d\n", a);
    printf("8进制: b = %o\n", b);
    printf("10进制: b = %d\n", b);
    printf("16进制: b = %x\n", c);
    printf("16进制: b = %X\n", c);
    printf("10进制: b = %d\n", c);

    unsigned int d = 0xffffffff;
    printf("有符号方式打印：d = %d\n", d);
    printf("无符号方式打印：d = %u\n", d);

    return 0;
}