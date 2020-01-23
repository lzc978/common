#include <stdio.h>

/*
char变量通常占用1byte, 将该字符的ASCII码存入变量储存单元
%c打印字符
%d打印字符的ascii, int也是打印ascii, 不过对应的就是数字
*/

int main()
{
    char ch = 'a';
    printf("sizeof(ch) = %u\n", sizeof(ch));
    printf("ch[%%c] = %c\n", ch); // 打印字符
    printf("ch[%%d] = %d\n", ch); // 打印'a'的ascii码

    char A = 'A';
    char a = 'a';
    printf("a = %d\n", a); // 打印对应的ascii码
    printf("A = %d\n", A);

    printf("A = %c\n", 'a' - 32); //小写a转大写A
    printf("a = %c\n", 'A' + 32); //大写A转小写a

    ch = ' ';
    printf("空字符：%d\n", ch); //空字符ASCII值为32
    printf("A = %c\n", 'a' - ' '); //相当于大小写转换
    printf("a = %c\n", 'A' + ' ');
}