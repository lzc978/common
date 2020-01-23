/**
 * 使用对象指针
 * C语言中经典的指针在 C++ 中仍然广泛使用，尤其是指向对象的指针，没有它就不能实现某些功能。
 * 上面代码中创建的对象 stu 在栈上分配内存，需要使用&获取它的地址，例如：
 * \code
 * Student stu;
 * Student *pStu = &stu;
 * \endcode
 * pStu 是一个指针，它指向 Student 类型的数据，也就是通过 Student 创建出来的对象。
 * 当然，你也可以在堆上创建对象，这个时候就需要使用前面讲到的new关键字（C++ new和delete运算符简介），例如：
 * \code
 * Student *pStu = new Student;
 * \endcode
 * 在栈上创建出来的对象都有一个名字，比如 stu，使用指针指向它不是必须的。但是通过 new 创建出来的对象就不一样了，它在堆上分配内存，没有名字，只能得到一个指向它的指针，所以必须使用一个指针变量来接收这个指针，否则以后再也无法找到这个对象了，更没有办法使用它。也就是说，使用 new 在堆上创建出来的对象是匿名的，没法直接使用，必须要用一个指针指向它，再借助指针来访问它的成员变量或成员函数。
 * 栈内存是程序自动管理的，不能使用 delete 删除在栈上创建的对象；堆内存由程序员管理，对象使用完毕后可以通过 delete 删除。在实际开发中，new 和 delete 往往成对出现，以保证及时删除不再使用的对象，防止无用内存堆积。
 * 栈（Stack）和堆（Heap）是 C/C++ 程序员必须要了解的两个概念
 * 有了对象指针后，可以通过箭头->来访问对象的成员变量和成员函数，这和通过结构体指针来访问它的成员类似，请看下面的示例：
 * \code
 * pStu -> name = "小明";
pStu -> age = 15;
pStu -> score = 92.5f;
pStu -> say();
    \endcode
 */ 

#include <iostream>
using namespace std;

class Student{
public:
    char *name;
    int age;
    float score;

    void say(){
        cout<<name<<"的年龄是"<<age<<"，成绩是"<<score<<endl;
    }
};

int main(){
    Student *pStu = new Student;
    pStu -> name = "小明";
    pStu -> age = 15;
    pStu -> score = 92.5f;
    pStu -> say();
    delete pStu;  //删除对象

    return 0;
}

//本节重点讲解了两种创建对象的方式：一种是在栈上创建，形式和定义普通变量类似；另外一种是在堆上使用 new 关键字创建，必须要用一个指针指向它，读者要记得 delete 掉不再使用的对象。
//通过对象名字访问成员使用点号.，通过对象指针访问成员使用箭头->，这和结构体非常类似。
