# 指针概述
**理解指针的关键在于内存**

## 内存
### 内存含义：
> 存储器：计算机的组成中，用来存储程序和数据，辅助CPU进行运算处理的重要部分。

> 内存：内部存贮器，暂存程序/数据——掉电丢失 SRAM、DRAM、DDR、DDR2、DDR3。

> 外存：外部存储器，长时间保存程序/数据—掉电不丢ROM、ERRROM、FLASH（NAND、NOR）、硬盘、光盘。

### 内存是沟通CPU与硬盘的桥梁：
> 暂存放CPU中的运算数据 

> 暂存与硬盘等外部存储器交换的数据

### 物理存储器和存储地址空间
**有关内存的两个概念：物理存储器和存储地址空间。**
> 物理存储器：实际存在的具体存储器芯片。
- 主板上装插的内存条 
- 显示卡上的显示RAM芯片 
- 各种适配卡上的RAM芯片和ROM芯片

> 存储地址空间：对存储器编码的范围。我们在软件上常说的内存是指这一层含义。
- 编码：对每个物理存储单元（一个字节）分配一个号码 
- 寻址：可以根据分配的号码找到相应的存储单元，完成数据的读写

### 内存地址 
> 将内存抽象成一个很大的一维字符数组。

> 编码就是对内存的每一个字节分配一个32位或64位的编号（与32位或者64位处理器相关）。

> 这个内存编号我们称之为内存地址。

> 内存中的每一个数据都会分配相应的地址：
- char:占一个字节分配一个地址 
- int: 占四个字节分配四个地址
- float、struct、函数、数组等

### 指针和指针变量
> 内存区的每一个字节都有一个编号，这就是“地址”。

> 如果在程序中定义了一个变量，在对程序进行编译或运行时，系统就会给这个变量分配内存单元，并确定它的内存地址(编号)

> 指针的实质就是内存“地址”。指针就是地址，地址就是指针。

> 指针是内存单元的编号，指针变量是存放地址的变量。

> 通常我们叙述时会把指针变量简称为指针，实际他们含义并不一样。
---
## 指针基础知识
### 指针变量的定义和使用
- 指针也是一种数据类型，指针变量也是一种变量
- 指针变量指向谁，就把谁的地址赋值给指针变量
- “*”操作符操作的是指针变量指向的内存空间
```
#include <stdio.h>

int main()
{
	int a = 0;
	char b = 100;
	printf("%p, %p\n", &a, &b); //打印a, b的地址

	//int *代表是一种数据类型，int*指针类型，p才是变量名
	//定义了一个指针类型的变量，可以指向一个int类型变量的地址
	int *p;
	p = &a;//将a的地址赋值给变量p，p也是一个变量，值是一个内存地址编号
	printf("%d\n", *p);//p指向了a的地址，*p就是a的值

	char *p1 = &b;
	printf("%c\n", *p1);//*p1指向了b的地址，*p1就是b的值

	return 0;
}
```
***注意：&可以取得一个变量在内存中的地址。但是，不能取寄存器变量，因为寄存器变量不在内存里，而在CPU里面，所以是没有地址的。***
### 通过指针间接修改变量的值
```
int a = 0;
int b = 11;
int *p = &a;

*p = 100;
printf("a = %d, *p = %d\n", a, *p);

p = &b;
*p = 22;
printf("b = %d, *p = %d\n", b, *p);
```
### 指针大小
- 使用sizeof()测量指针的大小，得到的总是：4或8
- sizeof()测的是指针变量指向存储地址的大小
- 在32位平台，所有的指针（地址）都是32位(4字节)
- 在64位平台，所有的指针（地址）都是64位(8字节)
```
	int *p1;
	int **p2;
	char *p3;
	char **p4;
	printf("sizeof(p1) = %d\n", sizeof(p1));
	printf("sizeof(p2) = %d\n", sizeof(p2));
	printf("sizeof(p3) = %d\n", sizeof(p3));
	printf("sizeof(p4) = %d\n", sizeof(p4));
	printf("sizeof(double *) = %d\n", sizeof(double *));
```
### 野指针和空指针
**指针变量也是变量，是变量就可以任意赋值，不要越界即可（32位为4字节，64位为8字节），但是，任意数值赋值给指针变量没有意义，因为这样的指针就成了野指针，此指针指向的区域是未知(操作系统不允许操作此指针指向的内存区域)。所以，野指针不会直接引发错误，操作野指针指向的内存区域才会出问题。**
```
int a = 100;
	int *p;
	p = a; //把a的值赋值给指针变量p，p为野指针， ok，不会有问题，但没有意义

	p = 0x12345678; //给指针变量p赋值，p为野指针， ok，不会有问题，但没有意义

	*p = 1000;  //操作野指针指向未知区域，内存出问题，err
```
但是，野指针和有效指针变量保存的都是数值，为了标志此指针变量没有指向任何变量(空闲可用)，C语言中，可以把NULL赋值给此指针，这样就标志此指针为空指针，没有任何指针。\
```	int *p = NULL;``` \
NULL是一个值为0的宏常量：\
```#define NULL    ((void *)0)```
### 万能指针void *
void *指针可以指向任意变量的内存空间：
```
void *p = NULL;

	int a = 10;
	p = (void *)&a; //指向变量时，最好转换为void *

	//使用指针变量指向的内存时，转换为int *
	*( (int *)p ) = 11;
	printf("a = %d\n", a);
```
### const修饰的指针变量
```
int a = 100;
int b = 200;

//指向常量的指针
//修饰*，指针指向内存区域不能修改，指针指向可以变
const int *p1 = &a; //等价于int const *p1 = &a;
//*p1 = 111; //err
p1 = &b; //ok

//指针常量
//修饰p1，指针指向不能变，指针指向的内存可以修改
int * const p2 = &a;
//p2 = &b; //err
*p2 = 222; //ok
```
## 指针和数组
### 数组名
**数组名字是数组的首元素地址，但它是一个常量：**
```	
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
printf("a = %p\n", a);
printf("&a[0] = %p\n", &a[0]);

//a = 10; //err, 数组名只是常量，不能修改
```
### 指针法操作数组元素
```
#include <stdio.h>

int  main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
	int n = sizeof(a) / sizeof(a[0]);
	
	for (i = 0; i < n; i++)
	{
		//printf("%d, ", a[i]);
		printf("%d, ", *(a+i));
	}
	printf("\n");

	int *p = a; //定义一个指针变量保存a的地址
	for (i = 0; i < n; i++)
	{
		p[i] = 2 * i;
	}

	for (i = 0; i < n; i++)
	{
		printf("%d, ", *(p + i));
	}
	printf("\n");


	return 0;
}
```
### 指针加减运算
**加法运算**
- 指针计算不是简单的整数相加
- 如果是一个int *，+1的结果是增加一个int的大小
- 如果是一个char *，+1的结果是增加一个char大小
```
#include <stdio.h>

int main()
{
	int a;
	int *p = &a;
	printf("%d\n", p);
	p += 2;//移动了2个int
	printf("%d\n", p);

	char b = 0;
	char *p1 = &b;
	printf("%d\n", p1);
	p1 += 2;//移动了2个char
	printf("%d\n", p1);

	return 0;
}
```
**通过改变指针指向操作数组元素：**
```
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
	int n = sizeof(a) / sizeof(a[0]);

	int *p = a;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", *p);
		p++;
	}
	printf("\n");
	
	return 0;
}
```
**减法运算**
```
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
	int n = sizeof(a) / sizeof(a[0]);

	int *p = a+n-1;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", *p);
		p--;
	}
	printf("\n");

	return 0;
}
```
### 指针数组
***指针数组，它是数组，数组的每个元素都是指针类型。***
```
#include <stdio.h>

int main()
{
	//指针数组
	int *p[3];
	int a = 1;
	int b = 2;
	int c = 3;
	int i = 0;

	p[0] = &a;
	p[1] = &b;
	p[2] = &c;

	for (i = 0; i < sizeof(p) / sizeof(p[0]); i++ )
	{
		printf("%d, ", *(p[i]));
	}
	printf("\n");
	
	return 0;
}
```
## 多级指针
- C语言允许有多级指针存在，在实际的程序中一级指针最常用，其次是二级指针。
- 二级指针就是指向一个一级指针变量地址的指针。
- 三级指针基本用不着，但考试会考。
```
int a = 10;
int *p = &a; //一级指针
*p = 100; //*p就是a

int **q = &p;
//*q就是p
//**q就是a

int ***t = &q;
//*t就是q
//**t就是p
//***t就是a
```
## 指针和函数
### 函数形参改变实参的值
```
#include <stdio.h>

void swap1(int x, int y)
{
	int tmp;
	tmp = x;
	x = y;
	y = tmp;
	printf("x = %d, y = %d\n", x, y);
}

void swap2(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int main()
{
	int a = 3;
	int b = 5;
	swap1(a, b); //值传递
	printf("a = %d, b = %d\n", a, b);

	a = 3;
	b = 5;
	swap2(&a, &b); //地址传递
	printf("a2 = %d, b2 = %d\n", a, b);

	return 0;
}
```
### 数组名做函数参数
**数组名做函数参数，函数的形参会退化为指针：**
```
#include <stdio.h>

//void printArrary(int a[10], int n)
//void printArrary(int a[], int n)
void printArrary(int *a, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int n = sizeof(a) / sizeof(a[0]);

	//数组名做函数参数
	printArrary(a, n); 
	return 0;
}
```
## 指针小结
定义 	 	说明 
int  i		定义整形变量 
int *p		定义一个指向int的指针变量 
int a[10]	定义一个有10个元素的数组，每个元素类型为int
int *p[10]	定义一个有10个元素的数组，每个元素类型为int*
int func()	定义一个函数，返回值为int型
int *func()	定义一个函数，返回值为int *型
int **p		定义一个指向int的指针的指针，二级指针
