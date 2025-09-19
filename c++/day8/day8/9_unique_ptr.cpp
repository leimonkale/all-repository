#include <iostream>
using namespace std;

#include <memory>

class Demo{
public:
    Demo(){
        cout << "Constructor called" << endl;
    }
    ~Demo(){
        cout << "Destructor called" << endl;
    }
    void show(){
        cout << "Inside show" << endl;
    }
};

void test()
{
    // unique_ptr<Demo> p(new Demo);

    // make_unique:创建独占的资源
    unique_ptr<Demo> p = make_unique<Demo>();

    // unique_ptr<Demo> p2(p);      //错误，unique_ptr不支持拷贝构造,是独占资源的
    unique_ptr<Demo> p2 = move(p);  //正确，使用move移交了 p对资源的使用权

    p2->show();
}
int main()
{
    test();
}