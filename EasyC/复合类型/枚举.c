// 枚举：将变量的值一一列举出来，变量的值只限于列举出来的值的范围内。
// 枚举类型定义：
/*
enum  枚举名
{
	枚举值表
};
*/
/*
在枚举值表中应列出所有可用值，也称为枚举元素。
枚举值是常量，不能在程序中用赋值语句再对它赋值。
枚举元素本身由系统定义了一个表示序号的数值从0开始顺序定义为0，1，2 …
*/
#include <stdio.h>

enum weekday
{
	sun = 2, mon, tue, wed, thu, fri, sat // 可以修改枚举元素的序号数值
} ;

enum bool // 实现一个布尔值类型
{
	flase, true
};

int main()
{
	enum weekday a, b, c;
	a = sun;
	b = mon;
	c = tue;
	printf("%d,%d,%d\n", a, b, c);

	enum bool flag;
	flag = true;

	if (flag == 1)
	{
		printf("flag为真\n");
	}
	return 0;
}
