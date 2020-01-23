/*
 * C++ 引入了命名空间的概念，计划重新编写库，将类、函数、宏等都统一纳入一个命名空间，这个命名空间的名字就是std。std 是 standard 的缩写，意思是“标准命名空间”。
*/

#include <iostream> //io流
#include <string>

int main1() {
    //声明命名空间std
    using namespace std; //声明std命名空间，std是c++标准命名空间，就能使用c++标准库
   
    //定义字符串变量
    string str;
    //定义 int 变量
    int age;
    //从控制台获取用户输入
    cin>>str>>age; //cin控制台输入
    //将数据输出到控制台
    cout<<str<<"已经成立"<<age<<"年了！"<<endl; //cout控制台输出,endl结束符
    return 0;
}

//如果希望在所有函数中都使用命名空间 std，可以将它声明在全局范围中，例如：
//声明命名空间std
using namespace std;

// 在 main() 函数中声明命名空间 std，它的作用范围就位于 main() 函数内部，如果在其他函数中又用到了 std，就需要重新声明，请看下面的例子：
void func(){
    //必须重新声明
    //using namespace std;
    cout<<"http://c.biancheng.net"<<endl;
}
int main(){
    //声明命名空间std
    using namespace std;
   
    cout<<"C语言中文网"<<endl;
    func();
    return 0;
}

/** C++变量的定义位置，取消了c99必须在开头定义的规定，可以自由定义，比如在for循环中定义
    \code
#include <iostream>
using namespace std;
int sum(int n){
    int total = 0;
    //在for循环的条件语句内部定义变量i
    for(int i=1; i<=n ;i++){
        total += i;
    }
    return total;
}
int main(){
    cout<<"Input a interge: ";
    int n;
    cin>>n;
    cout<<"Total: "<<sum(n)<<endl;
    return 0;
}
    \endcode 
 */

