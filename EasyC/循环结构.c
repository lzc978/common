#include <stdio.h>

//while循环语句

/*
int main()
{
    int a = 20;
    while (a > 10)
    {
        scanf("%d", &a);
        printf("a = %d\n", a);
    }
    return 0;
    
}
*/

//do...while循环语句
/*
int main()
{
    int a = 1;
    do //执行循环，直到while条件满足
    {
        a++;
        printf("a = %d\n", a);
    } while (a < 10);
    return 0;
}
*/

//for 循环语句

/*
int main()
{
    int i;
    int sum = 0;
    for ( i = 0; i <= 100; i++)
    {
        sum += i;
    }
    printf("sum = %d\n", sum);
    return 0;
}
*/

//嵌套循环
//循环 跳转语句
//break, continue, goto

//break
//switch条件语句中，break适用于终止某个case并跳出switch结构
//循环语句作用是跳出当前内循环代码

//continue
//循环中终止本次循环，执行下一次循环

//goto 无条件跳转（尽量少用）
int main()
{
    goto End;//无条件跳转到End标识
    printf("ok\n");
End:
    printf("no\n");
    return 0;
}