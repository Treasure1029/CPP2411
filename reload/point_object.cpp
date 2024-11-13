/*************************************************************************
	> File Name: point_object.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 12 Nov 2024 04:55:34 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public :
    int x, y;
};

class Point_A {
public : 
    Point_A(A *p) : p(p)

    A *operator->() {return p;}
    A &operator*() {return *p;}
    A *p;

};

ostream &operator<<(ostream &out,const A &a) {
    out << "(" << a.x << ", " << a.y << ")";
    return out;
}

int main() {
    A a;
    Point_A p = &a;
    p->x = 3;
    p->y = 4;

    cout << *p << endl;

    return 0;
}
