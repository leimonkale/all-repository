#include <iostream>
using namespace std;

class Graphic{
public:
    virtual ~Graphic() = 0;
    virtual double area() = 0;
};
Graphic::~Graphic(){}

class Circle : public Graphic{
    double r;
public:
    Circle(double r) : r(r){}
    double area(){
        return 3.14 * r * r;
    }
};
class Rectangle : public Graphic{
    double a, b;
public:
    Rectangle(double a, double b) : a(a), b(b){}
    double area(){
        return a * b;
    }
};
class Triangle : public Graphic{
    double a, h;
public:
    Triangle(double a, double h) : a(a), h(h){}
    double area(){
        return a * h / 2;
    }
};

int main()
{
    Graphic * p = new Circle(5);
    cout << p->area() << endl;
    delete p;

    p = new Rectangle(5, 10);
    cout << p->area() << endl;
    delete p;

    p = new Triangle(5, 10);
    cout << p->area() << endl;
    delete p;
}
