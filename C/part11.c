#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>

#define DEFLINES 5
#define MAXLEN 81
/* 输出文件倒数n行 */
struct Tail{
    char data[MAXLEN];
    struct Tail *link;
};

int main(int argc,char *argv[]) {
    char curline[MAXLEN], *filename;
    int n =DEFLINES,i;
    struct Tail *list,*ptr,*qtr;
    FILE *fp;
    if (argc==3&&argv[1][0]=='-'){
        n= atoi(argv[1]+1);
        filename=argv[2];
    }
    else if (argc==2){
        filename=argv[1];
    }
    else{
        fprintf(stderr,"Usage:tail [-n] filename\n");
        exit(1);
    }
    if ((fp = fopen(filename,"r"))==NULL){
        fprintf(stderr,"Cannot open file %s\n",filename);
        exit(1);
    }

    list = qtr = (struct Tail *) malloc(sizeof(struct Tail));
    qtr->data[0]='\0';
    for (int i = 1; i < n; i++) {
        ptr = (struct Tail *) malloc(sizeof(struct Tail));
        ptr->data[0]='\0';
        qtr->link=ptr;
        qtr=ptr;
    }
    ptr->link=list;

    ptr =list;
    while (fgets(curline,MAXLEN,fp)!=NULL){
        strcpy(ptr->data,curline);
        ptr=ptr->link;
    }
    for (int i = 0; i < n; i++) {
        printf("%s",ptr->data);
        ptr=ptr->link;
    }
    fclose(fp);
    return 0;
}

