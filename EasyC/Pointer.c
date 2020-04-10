#include <stdio.h>

extern int test(void);
extern int test_1(void);
extern int test_2(void);
extern int test_3(void);
extern int test_4(void);
extern int test_5(void);
extern int test_6(void);
extern int test_7(void);
extern int test_8(void);

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

    test();
    test_1();
    test_2();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
	return 0;
}
// 注意：&可以取得一个变量在内存中的地址。但是，不能取寄存器变量，因为寄存器变量不在内存里，而在CPU里面，所以是没有地址的。
// 寄存器变量：register int a;

// 通过指针间接修改变量的值
int test()
{
    int a = 0;
	int b = 11;
	int *p = &a;

	*p = 100; // 指针变量p为a的地址，*p为a的值，*p指向100的地址，则a为100
	printf("a = %d, *p = %d\n", a, *p);

	p = &b;
	*p = 22;
	printf("b = %d, *p = %d\n", b, *p);
}

// 指针大小
/*
	使用sizeof()测量指针的大小，得到的总是：4或8
	sizeof()测的是指针变量指向存储地址的大小
	在32位平台，所有的指针（地址）都是32位(4字节)
	在64位平台，所有的指针（地址）都是64位(8字节)
*/
int test_1()
{
    int *p1;
	int **p2;
	char *p3;
	char **p4;
	printf("sizeof(p1) = %d\n", sizeof(p1));
	printf("sizeof(p2) = %d\n", sizeof(p2));
	printf("sizeof(p3) = %d\n", sizeof(p3));
	printf("sizeof(p4) = %d\n", sizeof(p4));
	printf("sizeof(double *) = %d\n", sizeof(double *));
}

// 万能指针 void *
// void *指针可以指向任意变量的内存空间：
int test_2()
{
    void *p = NULL;

	int a = 10;
	p = (void *)&a; //指向变量时，最好转换为void *

	//使用指针变量指向的内存时，转换为int *
	*( (int *)p ) = 11;
	printf("a = %d\n", a);

}

// const修饰的指针变量
int test_3()
{
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
}


// 指针法操作数组元素
int test_4()
{
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i = 0;
    int n = sizeof(a) / sizeof(a[0]);
	
	for (i = 0; i < n; i++)
	{
		//printf("%d, ", a[i]);
		printf("%d, ", *(a+i)); // 因为数组的每个元素对应的地址都是连续的
	}
	printf("\n");

    int *p = a;//定义一个指针变量保存a的地址
    // 数组a变量是数组的首元素地址，但它是一个常量，int b &b也是个地址
    
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


// 指针加减运算
// 	如果是一个int *，+1的结果是增加一个int的大小
// 	如果是一个char *，+1的结果是增加一个char大小
#include <stdio.h>

int test_5()
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

// 通过改变指针指向操作数组元素：
int test_6()
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

// 2) 减法运算
int test_7()
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

// 指针数组
int test_8()
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
