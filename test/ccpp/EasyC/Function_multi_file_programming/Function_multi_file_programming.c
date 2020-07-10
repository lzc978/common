// 多文件(分文件)编程 \
	把函数声明放在头文件xxx.h中，在主函数中包含相应头文件 \
	在头文件对应的xxx.c中实现xxx.h声明的函数
// *.h *.c 在编译的时候多文件编译成一个可执行文件，这样会导致文件很大
// *.dll 就是动态加载的类库文件，就是.exe文件运行的时候动态加载，这样.exe就不会很大


// 防止头文件重复包含
// 当一个项目比较大时，往往都是分文件，这时候有可能不小心把同一个头文件 include 多次，或者头文件嵌套包含。

// 例如

/*
a.h

#include "b.h" //嵌套包含
*/

/*
b.h

#include "a.h" //互相嵌套包含，死循环，error
*/

/*
main.c

#include "a.h" // error, 死循环嵌套

int main()
{
	return 0;
}
*/

// 为了避免同一个文件被include多次，C/C++中有两种方式，一种是 #ifndef 方式，一种是 #pragma once 方式。

// 方法一：
#ifndef __SOMEFILE_H__ // __SOMEFILE_H__ 构成是：__文件名_后缀__
#define __SOMEFILE_H__

// 声明语句

#endif

// 方法二：
#pragma once

// 声明语句
