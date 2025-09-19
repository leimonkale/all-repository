
//标注输入输出头文件，由  istream 和 ostream 构成
#include <iostream>

// 声明使用标准名字空间  std
using namespace std;

int main()
{
    //2、const修饰变量为只读变量，永远只可读，通过指针也不能修改
    const int a = 12;
    // int *p = &a;
    int *p = (int *)&a;

    *p += 13;

    cout << "*p: " << *p << endl;
    cout << "a: " << a << endl;
}

