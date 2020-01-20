#include <stdio.h>

/*
一维数组的最值
*/

int main(){
    int a[] = {1, -2, 3,- 4, 5, -6, 7, -8, -9, 10};//定义一个数组，同时初始化所有成员变量
    int i = 0;
    int max = a[0];
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) //数组的元素个数sizeof(a) / sizeof(a[0])
    {
        max = (a[i] > max ? a[i] : max); // 三元运算
    }
    printf("max = %d\n", max);
    test();
    return 0;
}
 
// 一维数组的逆置

int test()
{
    int a[] = {1, -2, 3,- 4, 5, -6, 7, -8, -9, 10};//定义一个数组，同时初始化所有成员变量
    int i = 0;
    int j = sizeof(a) / sizeof(a[0]) - 1;
    int tmp;

    while (i < j)
    {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        i++;
        j--;
    }
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    demo();
    return 0;
}

// 冒泡排序

int demo()
{
    int a[] = {1, -2, 3,- 4, 5, -6, 7, -8, -9, 10};//定义一个数组，同时初始化所有成员变量
    int i = 0;
    int j = 0;
    int n = sizeof(a) / sizeof(a[0]);
    int tmp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }   
        }
    }
    for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
