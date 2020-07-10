/** 这段代码在类体中定义了成员函数。你也可以只在类体中声明函数，而将函数定义放在类体外面，如下图所示：
 * \code
 * class Student{
public:
    //成员变量
    char *name;
    int age;
    float score;
    //成员函数
    void say();  //函数声明
};
//函数定义
void Student::say(){
    cout<<name<<"的年龄是"<<age<<"，成绩是"<<score<<endl;
}
    \endcode
 * 在类体中直接定义函数时，不需要在函数名前面加上类名，因为函数属于哪一个类是不言而喻的。
 * 
 * 如果你既希望将函数定义在类体外部，又希望它是内联函数，那么可以在定义函数时加 inline 关键字。当然你也可以在函数声明处加 inline，不过这样做没有效果，编译器会忽略函数声明处的 inline，我们已在《如何规范地使用C++内联函数》中对这点进行了详细讲解。
 * \code
 * class Student{
public:
    char *name;
    int age;
    float score;
    void say();  //内联函数声明，可以增加 inline 关键字，但编译器会忽略
};
//函数定义, 内联函数say()
inline void Student::say(){
    cout<<name<<"的年龄是"<<age<<"，成绩是"<<score<<endl;
}
    \endcode
 */


/**
 * C++通过 public、protected、private 三个关键字来控制成员变量和成员函数的访问权限，它们分别表示公有的、受保护的、私有的，被称为成员访问限定符。所谓访问权限，就是你能不能使用该类中的成员。
 * C++ 中的 public、private、protected 只能修饰类的成员，不能修饰类，C++中的类没有共有私有之分。
 * 在类的内部（定义类的代码内部），无论成员被声明为 public、protected 还是 private，都是可以互相访问的，没有访问权限的限制。
 * 在类的外部（定义类的代码之外），只能通过对象访问成员，并且通过对象只能访问 public 属性的成员，不能访问 private、protected 属性的成员。
 */

#include <iostream>
using namespace std;

//类的声明
class Student{
private:  //私有的
    char *m_name;
    int m_age;
    float m_score;

public:  //共有的
    void setname(char *name);
    void setage(int age);
    void setscore(float score);
    void show();
};

//成员函数的定义
void Student::setname(char *name){
    m_name = name;
}
void Student::setage(int age){
    m_age = age;
}
void Student::setscore(float score){
    m_score = score;
}
void Student::show(){
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<endl;
}

int main(){
    //在栈上创建对象
    Student stu;
    stu.setname("小明");
    stu.setage(15);
    stu.setscore(92.5f);
    stu.show();

    //在堆上创建对象
    Student *pstu = new Student;
    pstu -> setname("李华");
    pstu -> setage(16);
    pstu -> setscore(96);
    pstu -> show();

    return 0;
}

/**
 * private 关键字的作用在于更好地隐藏类的内部实现，该向外暴露的接口（能通过对象访问的成员）都声明为 public，不希望外部知道、或者只在类内部使用的、或者对外部没有影响的成员，都建议声明为 private。
 * 根据C++软件设计规范，实际项目开发中的成员变量以及只在类内部使用的成员函数（只被成员函数调用的成员函数）都建议声明为 private，而只将允许通过对象调用的成员函数声明为 public。
 * 声明为 private 的成员和声明为 public 的成员的次序任意，既可以先出现 private 部分，也可以先出现 public 部分。如果既不写 private 也不写 public，就默认为 private。
 * 在一个类体中，private 和 public 可以分别出现多次。每个部分的有效范围到出现另一个访问限定符或类体结束时（最后一个右花括号）为止。但是为了使程序清晰，应该养成这样的习惯，使每一种成员访问限定符在类定义体中只出现一次。
 * \code
 * class Student{
private:
    char *m_name;
private:
    int m_age;
    float m_score;
public:
    void setname(char *name);
    void setage(int age);
public:
    void setscore(float score);
    void show();
};
    \endcode
 */
