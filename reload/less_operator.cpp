/*************************************************************************
	> File Name: less_operator.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 12 Nov 2024 03:46:34 PM CST
 ************************************************************************/

#include <iostream>
#include <map>
using namespace std;

class A {
public:
    A(int x = 0) : x(x) {}

    bool operator<(const A &a) const{
        return x < a.x;
    }
    bool operator>(const A &a) const {
        return a < *this;
    }
    bool operator==(const A &a) const {
        return !(*this < a) && !(a < *this);
    }
    bool operator!=(const A &a) const {
        return !(a == *this);
    }
    bool operator>=(const A &a) const {
        return (*this > a) || (*this == a);
    }
    bool operator<=(const A &a) const {
        return (*this < a) || (*this == a);
    }
    int x;
};

map<A,int> h;

#define P(stmt) {    \
    cout << #stmt << " : " << (stmt) << endl; \
}

int main() {
    A a(3), b(5);
    h[a] = 123;
    cout << h[a] << endl;

    P(a < b);
    P(a > b);
    P(a == b);
    P(a != b);
    P(a >= b);
    P(a <= b);

    return 0;
}

