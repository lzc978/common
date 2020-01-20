// 结构体普通变量做函数参数
#include<stdio.h>
#include <string.h>

extern void set_stu();//函数参数为结构体普通变量, 不能修改实参
extern void set_stu_pro();//函数参数为结构体指针变量, 实参被修改

//结构体类型的定义
struct stu
{
	char name[50];
	int age;
};

int main()
{
	struct stu s = { 0 };
    printf("s.name = %s, s.age = %d\n", s.name, s.age);
	set_stu(s); //值传递
    printf("s.name = %s, s.age = %d\n", s.name, s.age);
    set_stu_pro(&s);//指针变量传递
	printf("s.name = %s, s.age = %d\n", s.name, s.age);

	return 0;
}

//函数参数为结构体普通变量, 不能修改实参
void set_stu(struct stu tmp)
{
	strcpy(tmp.name, "mike");
	tmp.age = 18;
	printf("tmp.name = %s, tmp.age = %d\n", tmp.name, tmp.age);
}

// 结构体指针变量做函数参数
//函数参数为结构体指针变量
void set_stu_pro(struct stu *tmp)
{
	strcpy(tmp->name, "mike");
	tmp->age = 18;
}
