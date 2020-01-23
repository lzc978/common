// 利用strstr标准库函数找出一个字符串中substr出现的个数。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// while 

int main1(void)
{
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;

	while ((p = strstr(p, "abcd")) != NULL)
	{
		//能进来，肯定有匹配的子串
		//重新设置起点位置
		p = p + strlen("abcd");
		n++;

		if (*p == 0) //如果到结束符
		{
			break;
		}

	}

	printf("n = %d\n", n);

	return 0;
}

// do-while

int main(void)
{
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;

	do
	{
		p = strstr(p, "abcd");
		if (p != NULL)
		{
			n++; //累计个数

			//重新设置查找的起点
			p = p + strlen("abcd");

		}
		else //如果没有匹配的字符串，跳出循环
		{
			break;
		}
	} while (*p != 0); //如果没有到结尾

	printf("n = %d\n", n);
	return 0;
}
