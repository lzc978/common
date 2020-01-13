#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <arpa/inet.h> // 网络地址与二进制数之间的转换头文件
#include <errno.h>
#include <fcntl.h> //linux文件操作，文件锁等，属于stdio.h增强
#include <stdarg.h> //可变参数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //unix/linux相关函数，如获取进程id：getpid()

// 打印日志
void printlog(const char *fmt, ...);

// 错误处理
void err_sys(const char *fmt, ...);

// 设置非阻塞IO
void set_fl(int fd, int flags);
void clr_fl(int fd, int flags);

#endif
