#include <iostream>
using namespace std;

/*
    默认参数：
        1、C++中的函数的参数可以有初值，也就是默认参数
        2、默认参数只在函数声明时设置，定义时不能写。
        3、如果一个形参设置了默认参数，其后的所有形参都必须设置默认参数
        4、注意默认参数 和 函数重载， 调用传参时容易出现歧义
*/
int swap(int x = 10);

int func(int x, int y)
{
    return x+y;
}
int func(int x, int y, int z = 12)
{
    return x+y+z;
}
int main()
{
    cout << swap() << endl;                 //调用函数，采用默认参数
    cout << swap(20) << endl;               //调用函数，传参覆盖默认参数

    cout << func(1, 2, 3) << endl;
    // cout << func(1, 2) << endl;          //错误，有歧义，函数重载 和 默认参数
}



int swap(int x)
{
    return x;
}