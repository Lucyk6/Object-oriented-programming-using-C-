#include <iostream>
using namespace std;
class Number {
private:
    double value;
public:
    Number(double v) : value(v){}
    friend void shownumbers(Number n1, Number n2);

};
void shownumbers(Number n1, Number n2)
{
    cout << "nubers" << n1.value<< n2.value << endl;
  
}

int main()
{
    Number n1(45.4);
    Number n2(55.4);
    shownumbers(n1,n2);

}
2)
class Value
{
private:
    int first;
    int second;

public:
    Value(int f, int s) : first(f), second(s) {}

    friend int getSum(const Value& v);
};

int getSum(const Value& v)
{
    return v.first + v.second;
}

int main()
{
    Value f1(1000, 7);  
    Value s2(500, 9009);

    int sumF1 = getSum(f1);
    int sumS2 = getSum(s2);

    std::cout << "Sum of f1: " << sumF1 << std::endl;
    std::cout << "Sum of s2: " << sumS2 << std::endl;

    return 0;
}
