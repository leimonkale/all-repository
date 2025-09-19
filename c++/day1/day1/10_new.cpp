#include <iostream>
using namespace std;

#include <cstring>

int main()
{
    // new 开辟一个int型空间，空间初值为 5
    int *p = new int(5);
    char *q = new char('a');
    cout << *p << endl;
    //释放堆区空间
    delete p;


    //开辟5个int整型空间，开辟数组空间
    p = new int[5];
    //释放堆区数组空间
    delete [] p;


    q = new char[12];
    strcpy(q, "hello");
    delete [] q;
}