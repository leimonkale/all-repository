#include <iostream>
using namespace std;

template <class T>
class Demo{
public:
    Demo(T x): a(x){}
#if 0
    friend ostream& operator<<(ostream& out, Demo& obj){
        out << obj.a;
        return out;
    }
#else
    template <class B>
    friend ostream& operator<<(ostream& out, Demo<B>& obj);

    template <class C>
    friend C operator+(Demo<C>& obj1, Demo<C>& obj2);
#endif
private:
    T a;
};

template <class T>
ostream& operator<<(ostream& out, Demo<T>& obj){
    out << obj.a;
    return out;
}

template <class C, class D>
C operator+(Demo<C>& obj1, Demo<D>& obj2)
{
    return obj1.a + obj2.a;
}

int main()
{
    Demo <int> obj(5);
    cout << obj << endl;

    Demo <float> obj1(2.14);

    cout << obj + obj1 << endl;
}