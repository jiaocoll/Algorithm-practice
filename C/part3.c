#include<stdio.h>

/*
题目：打印出所有的“水仙花数”，所谓“水仙花数”是指一个三位数，其各位
数字立方和等于该数本身。例如：153是一个“水仙花数”，因为153=1的三次方
＋5的三次方＋3的三次方。
*/


void main()
{
    int n,a,b,c;
    for(n = 100 ; n <= 999 ; n++)
    {
        a = n / 100 ;

        b = n / 10 % 10 ;

        c = n % 100 % 10 ;

        if(a*a*a+b*b*b+c*c*c==n)
        {
            printf("%d  ",n);
        }

    }
    printf("\n");
}