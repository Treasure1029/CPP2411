/*************************************************************************
	> File Name: vector.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Wed 13 Nov 2024 08:14:28 AM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class my_vector {
public :
    typedef int *iterator;
    my_vector() : n(2), data(new int[n]), tail(0) {}
    void push_back(int x) {
        if (tail == n) {
            expand();
        }
        data[tail++] = x;
        return ;
    }
    size_t size() {return tail;}
    int &operator[](int ind) {return data[ind]; }
    iterator begin() {return data;}
    iterator end() {return data + tail;}
    

private :
    void expand() {
        int *new_data = new int[2 * n];
        for (int i = 0; i < tail; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cout << "expand : " << n << " -> " << 2 * n << endl;
        n *=2;
        return ;
    }

    int *data;
    size_t n, tail;
};


int main() {
    vector<int> a;
    my_vector b;

    // my_vector achieve
    for(int i = 0; i < 10; i++) {
        b.push_back(rand() % 100);
    }
    cout << "my_vector b push_back done" << endl;

    cout << "my_vector b for :" ;
    for(int i = 0; i < b.size(); i++) {
        cout << b[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < b.size(); i++) {
        b[i] = 3 * i;
    }
    cout << "my_vector b updata 3 * i done" << endl;
    cout << "my_vector::iterator : ";
    for(my_vector::iterator iter = b.begin(); iter != b.end(); iter++) {
        int x = *iter;
        cout << x << " ";
    }
    cout << endl;
    
    cout << "my_vector new for : ";
    for(int j : b) {
        cout << j << " ";
    }
    cout << endl;


    // vector achieve
    for(int i = 0; i < 10; i++) {
        a.push_back(rand() % 100);
    }

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < a.size(); i++) {
        a[i] = 2 * i;
    }
    
    for(vector<int>::iterator iter = a.begin(); iter != a.end(); iter++) {
        int x = *iter;
        cout << x << " ";
    }
    cout << endl;
    
    for(int j : a) {
        cout << j << " ";
    }
    cout << endl;

    return 0;
}

