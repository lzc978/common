/**
 * C语言并没有彻底从语法上支持“真”和“假”，只是用 0 和非 0 来代表。这点在 C++ 中得到了改善，C++ 新增了 bool 类型（布尔类型），它一般占用 1 个字节长度。bool 类型只有两个取值，true 和 false：true 表示“真”，false 表示“假”。
 */

#include <iostream>
using namespace std;
int main(){
    bool flag = true;
    if(flag){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }
    flag = false;
    if(flag){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }
    return 0;
}
