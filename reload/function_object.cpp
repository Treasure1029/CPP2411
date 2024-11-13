/*************************************************************************
	> File Name: function_object.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 12 Nov 2024 04:26:52 PM CST
 ************************************************************************/

#include<iostream>
#include <algorithm>

using namespace std;

class ADD {
public:
    int operator()(int a, int b) {
        cout << "class ADD function obeject : ";
        return a + b;
    }
};

class CMP {
public: 
    CMP(int tag = 0) : tag(tag) {}
    bool operator()(int a, int b) {
        cout << "tag : " << tag << endl;
        return a > b;
    }

    int tag;
};


void output(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return ;
}


int main()
{
    ADD add;
    cout << add(2 , 5) << endl;

    int buf[10] = {5, 4, 2, 1, 8, 7, 6, 10, 9, 3};
    sort(buf, buf + 10, CMP());
    output(buf, 10);
    

    return 0;
}

