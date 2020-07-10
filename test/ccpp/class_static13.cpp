/**
 * C++ static静态成员变量详解
 * 对象的内存中包含了成员变量，不同的对象占用不同的内存（已在《C++对象的内存模型》中提到），这使得不同对象的成员变量相互独立，它们的值不受其他对象的影响。例如有两个相同类型的对象 a、b，它们都有一个成员变量 m_name，那么修改 a.m_name 的值不会影响 b.m_name 的值。
 * 可是有时候我们希望在多个对象之间共享数据，对象 a 改变了某份数据后对象 b 可以检测到。共享数据的典型使用场景是计数，以前面的 Student 类为例，如果我们想知道班级中共有多少名学生，就可以设置一份共享的变量，每次创建对象时让该变量加 1。
 * 在C++中，我们可以使用静态成员变量来实现多个对象共享数据的目标。静态成员变量是一种特殊的成员变量，它被关键字static修饰，例如：
 * \code
 * class Student{
public:
    Student(char *name, int age, float score);
    void show();
public:
    static int m_total;  //静态成员变量
private:
    char *m_name;
    int m_age;
    float m_score;
};
    \endcode
 * static 成员变量属于类，不属于某个具体的对象，即使创建多个对象，也只为 m_total 分配一份内存，所有对象使用的都是这份内存中的数据。当某个对象修改了 m_total，也会影响到其他对象。
 * static 成员变量必须在类声明的外部初始化，具体形式为：
 * type class::name = value;
 * type 是变量的类型，class 是类名，name 是变量名，value 是初始值。将上面的 m_total 初始化：
 * int Student::m_total = 0;
 * 静态成员变量在初始化时不能再加 static，但必须要有数据类型。被 private、protected、public 修饰的静态成员变量都可以用这种方式初始化。
 * 注意：static 成员变量的内存既不是在声明类时分配，也不是在创建对象时分配，而是在（类外）初始化时分配。反过来说，没有在类外初始化的 static 成员变量不能使用。
 * static 成员变量既可以通过对象来访问，也可以通过类来访问。请看下面的例子：
 * \code
 * //通过类类访问 static 成员变量
Student::m_total = 10;
//通过对象来访问 static 成员变量
Student stu("小明", 15, 92.5f);
stu.m_total = 20;
//通过对象指针来访问 static 成员变量
Student *pstu = new Student("李华", 16, 96);
pstu -> m_total = 20;
    \endcode
 */

#include <iostream>
using namespace std;

class Student{
public:
    Student(char *name, int age, float score);
    void show();
private:
    static int m_total;  //静态成员变量
private:
    char *m_name;
    int m_age;
    float m_score;
};

//初始化静态成员变量
int Student::m_total = 0;

Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){
    m_total++;  //操作静态成员变量
}
void Student::show(){
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<"（当前共有"<<m_total<<"名学生）"<<endl;
}

int main(){
    //创建匿名对象
    (new Student("小明", 15, 90)) -> show();
    (new Student("李磊", 16, 80)) -> show();
    (new Student("张华", 16, 99)) -> show();
    (new Student("王康", 14, 60)) -> show();

    return 0;
}