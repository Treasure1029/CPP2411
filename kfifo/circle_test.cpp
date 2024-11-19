/*************************************************************************
	> File Name: circle_test.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 19 Nov 2024 08:16:04 AM CST
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#define P(a) { \
             printf("%s : %d\r\n", #a, a); \
             }

int main()
{
    unsigned char in = 0 , out = 0;
    unsigned char len = 25;

    in += len;

    while(1) {
        in+=len;
        out += len;
        P(in);
        P(out);
        P((unsigned char)(in-out));
        sleep(1);
    }


    return 0;
}

