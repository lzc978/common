#include <stdio.h>

/*
float               double 浮点型
4byte 7位有效数字    8byte 15~16位有效数字
因为浮点型储存空间有限, 所以会导致一些数字丢失, 有一些误差
*/

int main()
{
    //传统赋值
    float a = 3.14f; //后面有f的是float, 反之是double
    double b = 3.14;
    printf("a = %f\n", a); // %f 单精度浮点型
    printf("b = %lf\n", b); // %lf 双精度浮点型 double

    //科学法赋值
    float a1 = 3.2e3f; //3.2*1000 = 3200
    printf("a1 = %f\n", a1);
    return 0;
}