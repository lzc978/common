#include <stdio.h>

int a = 10;

int *getA()
{
	return &a;
}


int main()
{
	*( getA() ) = 111; // 指针可以修改变量的内存地址，返回值是指针变量，当然可以修改了
	printf("a = %d\n", a);

	return 0;
}
