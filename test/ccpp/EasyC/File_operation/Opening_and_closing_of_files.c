// 文件指针
// 在C语言中用一个指针变量指向一个文件，这个指针称为文件指针。 

typedef struct
{
	short           level;	//缓冲区"满"或者"空"的程度 
	unsigned        flags;	//文件状态标志 
	char            fd;		//文件描述符
	unsigned char   hold;	//如无缓冲区不读取字符
	short           bsize;	//缓冲区的大小
	unsigned char   *buffer;//数据缓冲区的位置 
	unsigned        ar;	 //指针，当前的指向 
	unsigned        istemp;	//临时文件，指示器
	short           token;	//用于有效性的检查 
}FILE;

// FILE是系统使用typedef定义出来的有关文件信息的一种结构体类型，结构中含有文件名、文件状态和文件当前位置等信息。
// 声明FILE结构体类型的信息包含在头文件“stdio.h”中，一般设置一个指向FILE类型变量的指针变量，然后通过它来引用这些FILE类型变量。通过文件指针就可对它所指的文件进行各种操作。 
// C语言中有三个特殊的文件指针由系统默认打开，用户无需定义即可直接使用: \
    stdin： 标准输入，默认为当前终端（键盘），我们使用的scanf、getchar函数默认从此终端获得数据。\
    stdout：标准输出，默认为当前终端（屏幕），我们使用的printf、puts函数默认输出信息到此终端。\
    stderr：标准出错，默认为当前终端（屏幕），我们使用的perror函数默认输出信息到此终端。


// 文件的打开
// 任何文件使用之前必须打开：
/*
#include <stdio.h>
FILE * fopen(const char * filename, const char * mode);
功能：打开文件
参数：
	filename：需要打开的文件名，根据需要加上路径
	mode：打开文件的模式设置
返回值：
	成功：文件指针
	失败：NULL
*/
#include <stdio.h>

// 第一个参数的几种形式:
int main(){
    FILE *fp_passwd = NULL;

    //相对路径：
    //打开当前目录passdw文件：源文件(源程序)所在目录
    FILE *fp_passwd = fopen("passwd.txt", "r");

    //打开当前目录(test)下passwd.txt文件
    fp_passwd = fopen(". / test / passwd.txt", "r");

    //打开当前目录上一级目录（相对当前目录）passwd.txt文件
    fp_passwd = fopen(".. / passwd.txt", "r");
        
    //绝对路径：
    //打开C盘test目录下一个叫passwd.txt文件
    fp_passwd = fopen("c://test//passwd.txt","r");
}
// 第二个参数的几种形式(打开文件的方式)：
/*
r或rb
以只读方式打开一个文本文件（不创建文件，若文件不存在则报错）
w或wb
以写方式打开文件(如果文件存在则清空文件，文件不存在则创建一个文件)
a或ab
以追加方式打开文件，在末尾添加内容，若文件不存在则创建文件
r+或rb+
以可读、可写的方式打开文件(不创建新文件)
r+或rb+
以可读、可写的方式打开文件(不创建新文件)
w+或wb+
以可读、可写的方式打开文件(如果文件存在则清空文件，文件不存在则创建一个文件)
a+或ab+
以添加方式打开文件，打开文件并在末尾更改文件,若文件不存在则创建文件
*/
/*
b是二进制模式的意思，b只是在Windows有效，在Linux用r和rb的结果是一样的
Unix和Linux下所有的文本文件行都是\n结尾，而Windows所有的文本文件行都是\r\n结尾
在Windows平台下，以“文本”方式打开文件，不加b：
当读取文件的时候，系统会将所有的 "\r\n" 转换成 "\n"
当写入文件的时候，系统会将 "\n" 转换成 "\r\n" 写入 
以"二进制"方式打开文件，则读\写都不会进行这样的转换
在Unix/Linux平台下，“文本”与“二进制”模式没有区别，"\r\n" 作为两个字符原样输入输出
*/
int main(void)
{
	FILE *fp = NULL;

	// "\\"这样的路径形式，只能在windows使用
	// "/"这样的路径形式，windows和linux平台下都可用，建议使用这种
	// 路径可以是相对路径，也可是绝对路径
	fp = fopen("../test", "w");
	//fp = fopen("..\\test", "w");

	if (fp == NULL) //返回空，说明打开失败
	{
		//perror()是标准出错打印函数，能打印调用库函数出错原因
		perror("open");
		return -1;
	}

	return 0;
}


// 文件的关闭
// 任何文件在使用后应该关闭：\
    打开的文件会占用内存资源，如果总是打开不关闭，会消耗很多内存 \
    一个进程同时打开的文件数是有限制的，超过最大同时打开文件数，再次调用fopen打开文件会失败 \
    如果没有明确的调用fclose关闭打开的文件，那么程序在退出的时候，操作系统会统一关闭。
/*
#include <stdio.h>
int fclose(FILE * stream);
功能：关闭先前fopen()打开的文件。此动作让缓冲区的数据写入文件中，并释放系统所提供的文件资源。
参数：
	stream：文件指针
返回值：
	成功：0
	失败：-1
*/
int test(){
FILE * fp = NULL;
fp = fopen("abc.txt", "r");
fclose(fp);
}
