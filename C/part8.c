#include <stdio.h>

void draw_line(int st, int len, int c1, int c2){//在终端屏幕上用len个字符画一条线，其中前st-1个是空格符，第st个和最后一个是c1其余是c2
    int i;

    for(i = 0;i < st-1;i++){
        putchar(' ');
    }
    putchar(c1);
    for(i = 1;i < len-1;i++){
        putchar(c2);
    }
    putchar(c1);
    putchar('\n');
}

void triangle(int hi, int c1, int c2){//在终端屏幕上画一个高度为hi的三角形，其边框为c1字符，内部用c2字符填充
    int i,j;
    for(i = 0;i < hi -1;i++){
        putchar(' ');
    }
    putchar(c1);
    putchar('\n');
    for(i = 1;i < hi-1;i++){
        draw_line(hi-i,i*2+1,c1,c2);
    }
    for (j = 0; j < hi * 2 -1 ; j++) {
        putchar(c1);
    }
    putchar('\n');

}

int main() {
    int h;
    char c1, c2;
    printf("请按右侧格式输入:h,c1,c2\n");
    scanf("%d,%c,%c",&h,&c1,&c2);
    if(h < 3 || h > 40){
        printf("The height must be between 3 and 40\n");
        return 1;
    }
    triangle(h,c1,c2);
    return 0;
}
