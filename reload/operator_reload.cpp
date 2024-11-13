/*************************************************************************
	> File Name: operator_reload.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 12 Nov 2024 10:39:31 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    A(int x, int y) : a(x), b(y)  {
        cout << this << " constructor " << endl;
    }
    A(A &a) : a(a.a), b(a.b) {
        cout << this << " copy constructor " << endl;
    }
    
    A(A &&a) : a(a.a), b(a.b) {
        cout << this << " move constructor" << endl;
        a.a = 0;
        a.b = 0;
    }

    void output() {
        cout << this << " (" << a << ", " << b << ") " << endl;
    }

    A &operator*=(int c) {
        a *= c, b*= c;
        return *this;
    }

    int a, b;

};

A operator+(A &x, A &y) {
    return move(A(x.a + y.a, x.b + y.b));
}

ostream &operator<<(ostream &out, const A &a) {
    out << "operator<< : (" << a.a << ", " << a.b << ")";
    return out;
}


int main()
{
    A a(1, 2), b(3, 4);
    A c = a + b;
    cout << c << " end" << endl;
    c *= 3;
    cout << c << " end" << endl;
    
    (c *= 1) *= 2;
    cout << c << " end" << endl;

    int n = 2;
    (n *= 3) *= 4;
    cout << "n = " << n << endl;
    return 0;
}

