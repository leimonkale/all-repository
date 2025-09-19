#include <iostream>
using namespace std;

#include <bitset>

int main()
{
    int a;
    cin >> a;
    cout << "a: " << a << endl;

    // cout.setf(ios::showbase);
    // cout.setf(ios::hex);
    // cout << a << endl;

    cout << hex << showbase << a << endl;
    cout << 15 << endl;

    cout << dec  << 11 << endl;

    cout << "0b" << bitset<8>(a) << endl;
}