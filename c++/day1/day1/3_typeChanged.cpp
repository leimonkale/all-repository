#include <iostream>
using namespace std;


int main()
{
    int a = 12, b = 13;
    // double c = (double)(a + b);
    double c = double(a+b);
    double d = double(3+2);             //类型转换也叫定义一个临时变量(对象)

    cout << c << endl;

}