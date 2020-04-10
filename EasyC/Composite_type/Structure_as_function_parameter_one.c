// 结构体数组名做函数参数

#include<stdio.h>

//结构体类型的定义
struct stu
{
	char name[50];
	int age;
};

//void set_stu_pro(struct stu tmp[100], int n)
//void set_stu_pro(struct stu tmp[], int n)
void set_stu_pro(struct stu *tmp, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		sprintf(tmp->name, "name%d%d%d", i, i, i);
		tmp->age = 20 + i;
		tmp++;
	}
}

int main()
{
	struct stu s[3] = { 0 };
	int i = 0;
	int n = sizeof(s) / sizeof(s[0]);
	set_stu_pro(s, n); //数组名传递

	for (i = 0; i < n; i++)
	{
		printf("%s, %d\n", s[i].name, s[i].age);
	}

	return 0;
}


// const修饰结构体指针形参变量
//结构体类型的定义
struct stu
{
	char name[50];
	int age;
};

void fun1(struct stu * const p)
{
	//p = NULL; //err
	p->age = 10; //ok
}

//void fun2(struct stu const*  p)
void fun2(const struct stu *  p)
{
	p = NULL; //ok
	//p->age = 10; //err
}

void fun3(const struct stu * const p)
{
	//p = NULL; //err
	//p->age = 10; //err
}
