#include <stdio.h>

/*
int main()
{
    int a = 1;
    int b = 2;
    if(a > b)
    {
        printf("%d\n", a);
    }
    else
    {
        printf("%d\n", b);
    }
    return 0;
}
*/
/*
int main()
{
    unsigned int a;
    scanf("%u", &a);

    if(a < 10)
    {
        printf("个位\n");
    }
    else if (a < 100)
    {
        printf("十位\n");
    }
    else
    {
        printf("其他\n");
    }
    return 0;
}
*/

// 三目运算符

/*
int main()
{
    int a = 10;
    int b = 20;
    int c;
    if(a>b)
    {
        c = a;
    }
    else
    {
        c = b;
    }
    printf("c1 = %d\n", c);
    a = 1;
    b = 2;
    c = (a > b ? a : b); //三目运算符，c=2
    printf("c2 = %d\n", c);
    return 0;
}
*/

// switch语句

int main()
{
    char c;
    c = getchar();//输入字符，scanf输入数据

    switch (c)//参数只能是整型变量(字符型，整数型，都是整型，单个的)
    {
    case '1':
        printf("OK\n");
        break;//switch语句遇到break就跳出中断
    case '2':
        printf("not ok\n");
        break;
    default://如果上面都不满足，那么执行default，有点像else
        break;
    }
    return 0;
}