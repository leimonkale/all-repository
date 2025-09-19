#include <iostream>
using namespace std;

class Demo{
public:
    void func1(){
        cout << "Demo::func1()" << endl;
    }
private:
    int x = 12;
    char ch = 'a';
    int y = 13;
};

class Base{
    virtual void func1(){
        cout << "Base::func1()" << endl;
    }
private:
    int x = 14;
    char ch = 'b';
    int y = 15;    
};


typedef void (*func_ptr)();
int main()
{
    Demo obj;
    cout << sizeof(obj) << endl;
    int *ptr = (int *)&obj;
    cout << *ptr << endl;
    cout << *((char *)ptr + 4) << endl;
    cout << *(ptr + 2) << endl;
    cout << "--------------------------" << endl;
    Base obj1;
    cout << sizeof(obj1) << endl;

    long long *ptr1 = (long long *)&obj1;     //将对象首地址转换为 double *，目的是取头 8字节
    long long vtable = *ptr1;              //取对象头 8字节,取到虚函数表首地址这个数值。
    long long *vptr = (long long *)vtable;    //将虚函数表首地址数值转换为 double *
    long long vfunc = *vptr;            //取虚函数表首地址，取到第一个虚函数地址的数值
    func_ptr f = (func_ptr)vfunc;       //将虚函数地址的数值转换为 func_ptr
    f();                                //调用虚函数

    int *ptr2 = (int *)(ptr1 + 1);
    cout << *ptr2 << endl;

    cout << *((char *)ptr2 + 4) << endl;

    cout << *(int *)((char *)ptr2 + 8) << endl;
}