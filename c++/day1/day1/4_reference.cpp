#include <iostream>
using namespace std;


int main()
{
    int a = 12;
    //引用：一种新的数据类型，就是给变量取别名。
    int& b = a;
    // int &c;          //错误，引用的定义必须初始化

    cout << b << endl;
    b++;
    cout << a << endl;
    cout << &b << " " << &a << endl;

    int *p = &a;
    int *& q = p;

    cout << *p << " " << *q << endl;
    cout << p << " " << q << endl;
    cout << &p << " " << &q << endl;

    const int& c = 13;      //给一个常数取别名，使用 const &引用类型
    int&& d = 13;           //右值引用，专门给临时对象取别名。
    cout << d << endl;
}