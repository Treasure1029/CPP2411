/*************************************************************************
	> File Name: array_object.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 12 Nov 2024 04:47:28 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Array {
public :
    Array() : data(new int[10]) {}
    int &operator[](int ind) {
        return data[ind];
    }
    ~Array() {
        delete[] data;
    }
    int *data;
};

int main() {
    Array a;
    for(int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
    }
    for(int i = 0; i < 10; i++) {
        cout << a[i] << " ";
    }
    cout << endl;


    return 0;
}


