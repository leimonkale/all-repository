#include <iostream>
using namespace std;

#define pri cout << "func: " << __func__ << endl;
class Demo{
public:
    Demo(int x): x(x){ pri; }
    ~Demo(){ pri; }
private:
    int x;
};

class Base{
public:
  Base(int x): x(x){ pri; }
  ~Base(){ pri; }
private:
    int x;
};
class Derived: public Base{
public:
    Derived(int x): obj(23), Base(x){ pri; }
    ~Derived(){ pri; }
private:
    Demo obj;
};

int main()
{
    Derived obj(23);
}