#include <stdio.h>  // #include是头文件包含, 这个代表头文件包含stdio.h这个头文件
// stdio.h在os的include目录下
// 所有'#'开头的行, 都代表预编译指令

int main() // main函数是c语言的程序执行入口
{
    // {}叫做代码块
    // 所有可执行语句必须在代码块中
    printf("hello world!\n"); // printf是c语言库函数, 功能是向标准输出设备输出一个字符串
    /*
    return代表函数执行完毕, 返回return代表程序的终止
    如果main函数定义的时候是int, 则return必须是一个整数; 如果定义的是void, 则return空
    在main函数中'return 0'代表程序执行成功, 'return -1'代表程序执行失败 
    */
    return 0;
}