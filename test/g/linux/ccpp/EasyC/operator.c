#include <stdio.h>
#include <string.h>

int main()
{
    //算术运算符
    int a = 1;
    int b = a++;//后自增
    printf("a = %d\n", a);//a = 2
    printf("b = %d\n", b);//b = 1
    b = ++a;//后自增
    printf("a = %d\n", a);//a = 3
    printf("b = %d\n", b);//b = 3
    // 后自增，则赋值给b的是自增前的，即赋值后再自增
    // 前自增，则相反
    // 前/后自减逻辑相同

    //赋值运算符
    memset(&a, 0, sizeof(a)); //memset用于初始化变量地址，重新为变量申请内存地址
    memset(&b, 0, sizeof(b)); //第一个变量是个指针(即变量地址编号)，第二个是设置变量内存大小byte，第三个是该变量内存大小
    a = 0;
    a+=2;//加等于，就是a=a+2；同理，减等于，乘等于...
    printf("a = %d\n", a);// a=2
    printf("b = %d\n", b);// b=0

    //比较运算符
    //逻辑运算符
    //运算符优先级
    return 0;
}