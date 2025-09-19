#include <iostream>
using namespace std;

/*
    函数重载：
        1、函数名相同
        2、返回值不管
        3、函数的参数不同(个数不同、类型不同)

    函数重载意义：
        1、方便程序员取函数名
*/
int swap(int x)
{
    return x;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
void swap(int&& x, int&& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
int main()
{
    int a = 12, b = 13;
    swap(&a, &b);           //地址传递
    cout << a << " " << b << endl;

    swap(a, b);             //引用传递
    cout << a << " " << b << endl;

    swap(move(a), move(b));  //右值引用传递
    cout << a << " " << b << endl;
}