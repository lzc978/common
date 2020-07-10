/**
 * 类和对象是 C++ 的重要特性，它们使得 C++ 成为面向对象的编程语言，可以用来开发中大型项目
 * 与结构体一样，类只是一种复杂数据类型的声明，不占用内存空间。而对象是类这种数据类型的一个变量，或者说是通过类这种数据类型创建出来的一份实实在在的数据，所以占用内存空间。
 * 类的定义
 * 类是用户自定义的类型，如果程序中要用到类，必须提前说明，或者使用已存在的类（别人写好的类、标准库中的类等），C++语法本身并不提供现成的类的名称、结构和内容。
 * \code
 * class Student{
public:
    //成员变量
    char *name;
    int age;
    float score;
    //成员函数
    void say(){
        cout<<name<<"的年龄是"<<age<<"，成绩是"<<score<<endl;
    }
};
    \endcode
 * 注意在类定义的最后有一个分号;，它是类定义的一部分，表示类定义结束了，不能省略。
 * 类只是一个模板（Template），编译后不占用内存空间，所以在定义类时不能对成员变量进行初始化，因为没有地方存储数据。只有在创建对象以后才会给成员变量分配内存，这个时候就可以赋值了。
 * 
 */

#include <iostream>
using namespace std;

//类通常定义在函数外面
class Student{
public:
    //类包含的变量
    char *name;
    int age;
    float score;
    //类包含的函数
    void say(){
        cout<<name<<"的年龄是"<<age<<"，成绩是"<<score<<endl;
    }
};

int main(){
    //创建对象
    Student stu;
    stu.name = "小明";
    stu.age = 15;
    stu.score = 92.5f;
    stu.say();
    return 0;
}
