#include <stdio.h>

void COPYSTR(char *str1,char *str2,int k){
    int n=0;
    while (n<k-1){
        str1++;
        n++;
    }
    while (*str1!='\0'){
        *str2++=*str1++;
    }
    *str2='\0';
}

int main() {
    int k;
    char str1[100], str2[100];
    printf("请输入第一段字符串：");
    gets(str1);
    printf("请输入k的值：");
    scanf("%d",&k);
    COPYSTR(str1,str2,k);
    printf("str1:%s\n",str1);
    printf("str2:%s\n",str2);
    return 0;
}

