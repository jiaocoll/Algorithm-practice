#include <stdio.h>

/*
    输入两个正整数m和n，求其最大公约数和最小公倍数。
*/
//辗转相除法
int main(){
    int p,r,m,n,temp;
    printf("请输入正整数m:");
    scanf("%d",&m);
    printf("请输入正整数n:");
    scanf("%d",&n);

    if(n<m){
        temp = n;
        n = m;
        m = temp;
    }
    p = m * n;
    while(m!=0){
        r = n%m;
        n = m;
        m = r;
    }
    printf("最大公约数:%d\n",n);
    printf("最小公倍数:%d\n",p/n);
    return 0;

}
