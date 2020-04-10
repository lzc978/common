/*
当调用函数时，需要关心5要素：
	头文件：包含指定的头文件
	函数名字：函数名字必须和头文件声明的名字一样
	功能：需要知道此函数能干嘛后才调用
	参数：参数类型要匹配
	返回值：根据需要接收返回值

*/

/*
#include <time.h>
time_t time(time_t*t);
功能：获取当前系统时间
参数：常设置为NULL
返回值：当前系统时间, time_t 相当于long类型，单位为毫秒

#include <stdlib.h>
void srand(unsigned int seed);
功能：用来设置rand()产生随机数时的随机种子
参数：如果每次seed相等，rand()产生随机数相等
返回值：无

#include <stdlib.h>
int rand(void);
功能：返回一个随机数值
参数：无
返回值：随机数
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main()
{
    // 每调用一个函数，需要接收该函数的返回值，该返回值变量类型要和函数返回值对应，比如：time_t, sizef_t ....
    // NULL为空, 和Python中None, Numpy中NaN 等类似
    time_t tm = time(NULL); //得到系统时间
    srand((unsigned int) tm);//因为系统时间每次都不一样，seed参数用时间所以产生的随机数也不一样
    int r = rand();//返回一个随机数值
    printf("r = %d\n", r);

    test();
    return 0;
}

int test()
{
    /*
    #include <stdio.h>
    char *gets(char *s);
    功能：从标准输入读入字符，并保存到s指定的内存空间，直到出现换行符或读到文件结尾为止。
    参数：
        s：字符串首地址
    返回值：
        成功：读入的字符串
        失败：NULL
    */
    // gets(str)与scanf(“%s”,str)的区别：\
        gets(str)允许输入的字符串含有空格 \
        scanf(“%s”,str)不允许含有空格
    // 注意：由于scanf()和gets()无法知道字符串s大小，必须遇到换行符或读到文件结尾为止才接收输入，因此容易导致字符数组越界(缓冲区溢出)的情况。
    char str[100];
	printf("请输入str: ");
	gets(str);
	printf("str = %s\n", str);

    /*
    #include <stdio.h>
    char *fgets(char *s, int size, FILE *stream);
    功能：从stream指定的文件内读入字符，保存到s所指定的内存空间，直到出现换行字符、读到文件结尾或是已读了size - 1个字符为止，最后会自动加上字符 '\0' 作为字符串结束。
    参数：
        s：字符串
        size：指定最大读取字符串的长度（size - 1）
        stream：文件指针，如果读键盘输入的字符串，固定写为stdin
    返回值：
        成功：成功读取的字符串
        读到文件尾或出错： NULL
    */
    // fgets()在读取一个用户通过键盘输入的字符串的时候，同时把用户输入的回车也做为字符串的一部分。通过scanf和gets输入一个字符串的时候，不包含结尾的“\n”，但通过fgets结尾多了“\n”。fgets()函数是安全的，不存在缓冲区溢出的问题。
    char str[100];
	printf("请输入str: ");
	fgets(str, sizeof(str), stdin);
	printf("str = \"%s\"\n", str);

    /*
    #include <stdio.h>
    int puts(const char *s);
    功能：标准设备输出s字符串，在输出完成后自动输出一个'\n'。
    参数：
        s：字符串首地址
    返回值：
        成功：非负数
        失败：-1
    */
   	printf("hello world");
	puts("hello world");

    /*
    #include <stdio.h>
    int fputs(const char * str, FILE * stream);
    功能：将str所指定的字符串写入到stream指定的文件中， 字符串结束符 '\0'  不写入文件。 
    参数：
        str：字符串
        stream：文件指针，如果把字符串输出到屏幕，固定写为stdout
    返回值：
        成功：0
        失败：-1
    */
    // fputs()是puts()的文件操作版本，但fputs()不会自动输出一个'\n'。
    printf("hello world");
	puts("hello world");
	fputs("hello world", stdout);

    /*
    #include <string.h>
    size_t strlen(const char *s);
    功能：计算指定指定字符串s的长度，不包含字符串结束符‘\0’
    参数：
    s：字符串首地址
    返回值：字符串s的长度，size_t为unsigned int类型
    */
   	char str[] = "abcdefg";
	int n = strlen(str);
	printf("n = %d\n", n);

    /*
    #include <string.h>
    char *strcpy(char *dest, const char *src);
    功能：把src所指向的字符串复制到dest所指向的空间中，'\0'也会拷贝过去
    参数：
        dest：目的字符串首地址
        src：源字符首地址
    返回值：
        成功：返回dest字符串的首地址
        失败：NULL
    */
    // 注意：如果参数dest所指的内存空间不够大，可能会造成缓冲溢出的错误情况。
    char dest[20] = "123456789";
	char src[] = "hello world";
	strcpy(dest, src);
	printf("%s\n", dest);

    
}