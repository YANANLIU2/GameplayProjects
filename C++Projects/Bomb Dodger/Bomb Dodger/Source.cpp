#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Integar
{
public:
    int i;
    char ch;
    Integar(int j = 10)
    {
        this->i = j;
        ch = 'a';
    }
    Integar& operator++();
    Integar operator++(int);
};
Integar& Integar::operator++()
//????
{
    (this->i) += 1;
    return *this;
}
Integar Integar::operator++(int)
//????
{
    Integar temp = *this;
    (this->i) += 1;
    return temp;
}
ostream& operator<<(ostream& out, Integar& in)
{
    out << in.i << endl;
}
//??????<<???
const Integar operator+(const Integar& i, const Integar& j)//????????????????
{
    return Integar(i.i + j.i);
}
int main()
{
    Integar num1(15);
    Integar num2 = num1 + 100;
    cout << num2 << endl;
    cout << num2++ << endl;
    return 0;
}