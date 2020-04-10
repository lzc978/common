#include <stdio.h>

void mystrcat(char *dest, const char *src)
{
	int len1 = 0;
	int len2 = 0;
	while (dest[len1]) // 字符数组的最后一位是0 or '\0', 所以为false
	{
		len1++;
	}
	while (src[len2])
	{
		len2++;
	}

	int i;
	for (i = 0; i < len2; i++)
	{
		dest[len1 + i] = src[i]; // 指针形参，能够改变实参的值
	}
}

int main()
{
	char dst[100] = "hello mike";
	char src[] = "123456";
	
	mystrcat(dst, src);
	printf("dst = %s\n", dst);

	return 0;
}
