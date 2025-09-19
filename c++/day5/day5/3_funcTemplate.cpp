#include <iostream>
using namespace std;


//声明一个函数模板，  模板参数 T 代替了数据类型， T为类型模板形参
template<class T> T func(T x, T y);

//定义一个函数模板
template<typename B> B func(B x, B y)
{
    return x + y;
}

int main()
{
    // 1、隐式调用函数模板，根据实参的类型 自动确认 模板形参 T的值
    cout << func(1, 2) << endl;         // int func(int x, int y);
    cout << func(1.13, 2.14) << endl;   // double func(double x, double y);

    //2、显示调用函数模板，根据实参的类型 自动确认 模板形参 T的值
    cout << func< >(1, 2) << endl;
    cout << func< >(1.13, 2.14) << endl;

    //3、显示调用函数模板，明确指定 模板形参 T的值
    cout << func<int>(1, 2) << endl;
    cout << func<double>(1.13, 2.14) << endl;
}