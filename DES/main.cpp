#include<stdio.h>
#include<string.h>
#include"MyFun.h"   //自定义函数


int main(){
    char *M="0000000100100011010001010110011110001001101010111100110111101111";
    char *K="0001001100110100010101110111100110011011101111001101111111110001";
    char *MI;
    char *Ming;
    MI = encrypt(M,K);  //加密函数，并返回加密后的密文
    Ming = decrypt(MI,K);   //解密函数，并返回解密后的明文
    return 0;
}