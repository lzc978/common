#include <stdio.h>

/*
getchar是从标准输入设备读取到一个char
scanf通过%转义的方式可以得到用户通过标准输入设备输入的数据
*/

int main()
{
    char ch1;
    char ch2;
    char ch3;
    int a;
    int b;

    printf("请输入ch1的字符：");
    ch1 = getchar();
    printf("ch1 = %c\n", ch1);
    getchar();//测试此处getchar()的作用
    printf("请输入ch2的字符：");
    ch2 = getchar();
    printf("\'ch2 = %ctest\'\n", ch2);
    getchar();//测试此处getchar()的作用
    printf("请输入ch3的字符：");
    scanf("%c", &ch3);//这里第二个参数一定是变量的地址，而不是变量名
    // &ch3 变量名前面加&，代表变量地址
    printf("ch3 = %c\n", ch3);

    return 0;
}
