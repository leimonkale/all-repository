#include <iostream>

using namespace std;

int gloable = 12;
void print()
{
    cout << "gloable ...." << endl;
}

//命名声明区  ， Myspace就被称为 名字空间
namespace Myspace{
    int gloable = 13;
    void print()
    {
        cout << "local ...." << endl;
    }
}

// using namespace Myspace;     //全局声明使用 名字空间，空间中的名称直接使用；注意不要和 全局、局部形成歧义


int main()
{
    int gloable = 14;
    cout << gloable << endl;
    cout << ::gloable << endl;      // :: 作用域访问符
    ::print();
    cout << Myspace::gloable << endl;   // 单次说明访问 名字空间的 哪个名称
    Myspace::print();

    using Myspace::gloable;             //声明使用 名字空间的哪个名称，声明后直接使用 名称
    cout << gloable << endl;

    using Myspace::print;
    print();

    cout << gloable << endl;
    print();
}