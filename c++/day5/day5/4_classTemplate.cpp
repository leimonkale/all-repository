#include <iostream>
using namespace std;


//声明一个类模板
template <class T>
class Demo{
public:
    Demo(T x);
    void setValue(T x);
    T getValue();
private:
    T x;
};

//类模板成员函数类体外定义，每一个都必须用 template关键字说明为模板
template <class B>
Demo<B>::Demo(B x) : x(x)
{
}
template <class T>
void Demo<T>::setValue(T x)
{
    this->x = x;
}
template <class C>
C Demo<C>::getValue()
{
    return x;
}
int main()
{
    Demo<int> obj(12);              //类模板定义对象，必须显示使用，指定数据类型
    obj.setValue(13);
    cout << obj.getValue() << endl;

    Demo<char> obj1('c');
    obj1.setValue('a');
    cout << obj1.getValue() << endl;
}