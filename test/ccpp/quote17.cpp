/**
 * 我们知道，参数的传递本质上是一次赋值的过程，赋值就是对内存进行拷贝。所谓内存拷贝，是指将一块内存上的数据复制到另一块内存上。
 * 对于像 char、bool、int、float 等基本类型的数据，它们占用的内存往往只有几个字节，对它们进行内存拷贝非常快速。而数组、结构体、对象是一系列数据的集合，数据的数量没有限制，可能很少，也可能成千上万，对它们进行频繁的内存拷贝可能会消耗很多时间，拖慢程序的执行效率。
 * 引用的定义方式类似于指针，只是用&取代了*，语法格式为：
 * type &name = data;
 * type 是被引用的数据的类型，name 是引用的名称，data 是被引用的数据。引用必须在定义的同时初始化，并且以后也要从一而终，不能再引用其它数据，这有点类似于常量（const 变量）。
 * \code
 * #include <iostream>
using namespace std;
int main() {
    int a = 99;
    int &r = a;
    cout << a << ", " << r << endl;
    cout << &a << ", " << &r << endl;
    return 0;
}
    \endcode
本例中，变量 r 就是变量 a 的引用，它们用来指代同一份数据；也可以说变量 r 是变量 a 的另一个名字。从输出结果可以看出，a 和 r 的地址一样，都是0x28ff44；或者说地址为0x28ff44的内存有两个名字，a 和 r，想要访问该内存上的数据时，使用哪个名字都行。

注意，引用在定义时需要添加&，在使用时不能添加&，使用时添加&表示取地址。如上面代码所示，第 6 行中的&表示引用，第 8 行中的&表示取地址。除了这两种用法，&还可以表示位运算中的与运算。

 */ 

#include <iostream>
using namespace std;

void swap1(int a, int b);
void swap2(int *p1, int *p2);
void swap3(int &r1, int &r2);


int main() {
    int num1, num2;
    cout << "Input two integers: ";
    cin >> num1 >> num2;
    swap1(num1, num2);
    cout << num1 << " " << num2 << endl;

    cout << "Input two integers: ";
    cin >> num1 >> num2;
    swap2(&num1, &num2);
    cout << num1 << " " << num2 << endl;

    cout << "Input two integers: ";
    cin >> num1 >> num2;
    swap3(num1, num2);
    cout << num1 << " " << num2 << endl;

    return 0;
}

//直接传递参数内容
void swap1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

//传递指针
void swap2(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

//按引用传参
void swap3(int &r1, int &r2) {
    int temp = r1;
    r1 = r2;
    r2 = temp;
}
