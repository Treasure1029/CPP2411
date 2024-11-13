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
    // 前++
    A &operator++() {
        x += 1;
        return *this;
    }
    // 后++   int为占位符
    A operator++(int) {
        A ret(*this);
        x += 1;
        return ret;
    }
    int x;
};

map<A,int> h;

#define P(stmt) {    \
    cout << #stmt << " : " << (stmt) << endl; \
}

/*
A &operator++(A &a) {
    a.x += 1;
    return a;
}
*/
ostream &operator<<(ostream &out, const A &a) {
    out << "class A : x = " << a.x;
    return out;
}

int main() {
    A a(3), b(5);
    cout << a << endl;
    cout << "++a : " << ++a << endl;
    cout << "a++ : " << a++ << endl;
    cout << "a   : " << a << endl;

    return 0;
}

