/*
#include <stdio.h>
int system(const char *command);
// system()的功能是在一个已经运行的程序中执行另外一个程序
// system()就是调用不同系统的终端命令, 如windows下的calc
// system()中参数是外部可执行程序的名称
// system()返回值：成功：不同系统返回不一致 失败：通常是-1
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("notepad"); // windows 计算器 执行终端命令
    // system("ls"); // linux 需要头文件stdlib.h 执行终端命令

    return 0;
}