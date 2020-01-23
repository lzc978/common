#include <stdio.h>

int main()
{
	char str[] = "hello world";
	char *p = str; //p字符指针变量，接收的是一个字符数组（字符串）指针类型
	*p = 'm';// *p，反过来，对应的是字符数组，首元素的地址
	p++;
	*p = 'i';
	printf("%s\n", str);
    printf("%s\n", p); // p指针变量，p++，导致首元素地址后移了一位

	p = "mike jiang"; // 字符指针变量，可以直接赋值字符串
	printf("%s\n", p);

	char *q = "test";
	printf("%s\n", q);

	return 0;
}
