#include <stdio.h>
#include "fun.h" // include "" 代表第三方库 include <> 代表系统库

int main(void)
{
    int a = 10, b = 20, max_num, min_num;
    max_num = max(a, b);
    min_num = min(a ,b);
    printf("max_num = %d\n", max_num);
    printf("min_num = %d\n", min_num);
    return 0;
}
