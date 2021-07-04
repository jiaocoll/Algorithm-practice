#include <stdio.h>

/*
    输出所有的水仙花数:一个3位数，其各位数字立方和等于该数本身。
*/

int main(){
    
    int i,j,k,n;
    printf("所有的水仙花数如下:\n");
    for(n=100;n<1000;n++){
        i = n/100;
        j = n/10-i*10;
        k = n%10;
        if(n == i*i*i + j*j*j + k*k*k){
            printf("%d\n",n);
        }
    }
    return 0;
}
