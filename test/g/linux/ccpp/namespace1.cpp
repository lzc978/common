#include <stdio.h>

/**
 * 使用变量、函数时要指明它们所在的命名空间。以上面的 fp 变量为例，可以这样来使用：
 * \code
 * Li::fp = fopen("one.txt", "r");  //使用小李定义的变量 fp
 * Han::fp = fopen("two.txt", "rb+");  //使用小韩定义的变量 fp
 * \endcode
 * ::是一个新符号，称为域解析操作符，在C++中用来指明要使用的命名空间。
 * 除了直接使用域解析操作符，还可以采用 using 关键字声明，例如：
 * \code
 * using Li::fp;
 * fp = fopen("one.txt", "r");  //使用小李定义的变量 fp
 * Han :: fp = fopen("two.txt", "rb+");  //使用小韩定义的变量 fp
 * \endcode
 * 在代码的开头用using声明了 Li::fp，它的意思是，using 声明以后的程序中如果出现了未指明命名空间的 fp，就使用 Li::fp；但是若要使用小韩定义的 fp，仍然需要 Han::fp。
 * using 声明不仅可以针对命名空间中的一个变量，也可以用于声明整个命名空间，例如：
 * \code
 * using namespace Li;
 * fp = fopen("one.txt", "r");  //使用小李定义的变量 fp
 * Han::fp = fopen("two.txt", "rb+");  //使用小韩定义的变量 fp
 * \endcode
 */

//将类定义在命名空间中
namespace Diy{
    class Student{
    public:
        char *name;
        int age;
        float score;
  
    public:
        void say(){
            printf("%s的年龄是 %d，成绩是 %f\n", name, age, score);
        }
    };
}

int main(){
    Diy::Student stu1; //域解析操作符
    stu1.name = "小明";
    stu1.age = 15;
    stu1.score = 92.5f;
    stu1.say();

    return 0;
}
