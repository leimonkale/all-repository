#include <iostream>
using namespace std;


// 声明链接 C语言的函数
extern "C" int add(int, int);

int main()
{
    int a = 1, b = 2;

    //调用C函数
    cout << add(a, b) << endl;
}