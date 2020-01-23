#include <stdio.h>

/*
short(短整型): 2byte;
int(整型): 4byte;
long(长整型): windows 4byte, linux32 4byte, linux 64 8byte;
long long(长长整型): 8byte;
*/

int main()
{
    int a;
    printf("请输入a的值：");

    scanf("%d", &a);
    printf("a = %d\n", a);
    return 0;
}
