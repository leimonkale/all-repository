#include <iostream>
using namespace std;

class Demo{
public:
  explicit Demo(int x):a(x){
    cout << "Constructor called" << endl;
  }
  void print(){
    cout << a << endl;
  }
private:
  int a;
};

int main()
{
    //将 12隐式转换为 Demo类型的对象，隐式转换时就调用 有参构造
    // Demo obj = 12;               //错误，有参构造函数被 explicit 修饰，不能被隐式转换
    
    Demo obj(12);
    obj.print();
}