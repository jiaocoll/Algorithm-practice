#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *link;
}*Linklist;

int main() {
    Linklist list,p,r;
    int i,k,a;
    printf("亲输入k：");
    scanf("%d",&k);
    list = (Linklist) malloc(sizeof(struct node)); //第一个结点
    r=list;
    for(i=1;i<k;i++){
        p=(Linklist) malloc(sizeof(struct node));
        r->link=p;
        r=p;
    }
    r->link=list; //构建循环链表
    p=list;
    printf("请输入一系列数作为链表结点的数据：");
    while (scanf("%d",&a)&&a>=0){
        p->data=a;
        p=p->link;
    }
    r=p;
    printf("最后%d个数为：",k);
    do {
        printf(" %d",p->data);
        p=p->link;
    } while (p!=r);
    return 0;
}

