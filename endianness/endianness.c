/*************************************************************************
	> File Name: endianness.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Nov 2024 08:12:56 PM CST
 ************************************************************************/

#include<stdio.h>


union {
    int x;
    char bit[4];

} a;

#define PRINT(DATA) { \
    printf("%s is 0x%x \r\n", #DATA, DATA); \
}


int main()
{
    a.x = 0x12345678;
    PRINT(a.x);
    for(int i = 0; i < 4; i++) {
        printf("%p [0x%02x]\r\n", &a.bit[i], a.bit[i]);
    }


    return 0;
}



