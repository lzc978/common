// 按照字符读写文件fgetc、fputc
// 写文件
/*
#include <stdio.h>
int fputc(int ch, FILE * stream);
功能：将ch转换为unsigned char后写入stream指定的文件中
参数：
	ch：需要写入文件的字符
	stream：文件指针
返回值：
	成功：成功写入文件的字符
	失败：返回-1
*/
int main(){
    char buf[] = "this is a test for fputc";
    int i = 0;
    int n = strlen(buf);
    for (i = 0; i < n; i++)
    {
        //往文件fp写入字符buf[i]
        int ch = fputc(buf[i], fp);
        printf("ch = %c\n", ch);
    }
}


// 文件结尾
// 在C语言中，EOF表示文件结束符(end of file)。在while循环中以EOF作为文件结束标志，这种以EOF作为文件结束标志的文件，必须是文本文件。在文本文件中，数据都是以字符的ASCII代码值的形式存放。我们知道，ASCII代码值的范围是0~127，不可能出现-1，因此可以用EOF作为文件结束标志。
#define EOF     (-1)
// 当把数据以二进制形式存放到文件中时，就会有-1值的出现，因此不能采用EOF作为二进制文件的结束标志。为解决这一个问题，ANSI C提供一个feof函数，用来判断文件是否结束。feof函数既可用以判断二进制文件又可用以判断文本文件。
/*
#include <stdio.h>
int feof(FILE * stream);
功能：检测是否读取到了文件结尾。判断的是最后一次“读操作的内容”，不是当前位置内容(上一个内容)。
参数：
	stream：文件指针
返回值：
	非0值：已经到文件结尾
	0：没有到文件结尾
*/


// 读文件
/*
#include <stdio.h>
int fgetc(FILE * stream);
功能：从stream指定的文件中读取一个字符
参数：
	stream：文件指针
返回值：
	成功：返回读取到的字符
	失败：-1
*/
char ch;
#if 0
while ((ch = fgetc(fp)) != EOF)
{
	printf("%c", ch);
}
printf("\n");
#endif

while (!feof(fp)) //文件没有结束，则执行循环
{
	ch = fgetc(fp);
	printf("%c", ch);
}
printf("\n");
