#include<stdio.h>
#include<string.h>
#include"tables.h"


/*
置换函数
参数：
In：待置换数据指针
Out：置换输出指针
n:置换表长度
P：置换表指针
说明：将输入数据的指定位置作为输出数据的第i位。指定位置即置换表第i位的十进制数。得到的输出数据的长度
即为置换表的长度。
*/
void myPermutation(char *In,char *Out,int n,char *P)
{
    int i=0;
    for(i=0; i<n; i++)
        *(Out+i)=*(In+*(P+i)-1);
    *(Out+i)='\0';
}

/*
按位异或函数
参数：
In1：二进制串1
In2：二进制串2
n：二进制串长度
 Out:异或结果
说明：循环比较两个二进制串每一位，不同则为'1'，相同则为'0'
*/
void myXOR(char* In1,char* In2,int n,char* Out)
{
    int i=0;
    for(i=0; i<n; i++)
        *(In1+i)!=*(In2+i) ? *(Out+i)='1' : *(Out+i)='0';
}

/*
循环左移函数
参数：
In:待移位二进制串
Out:移位后二进制串
n:二进制串长度
s:循环位数
说明：将输入二进制串移位后对应位置的值赋给输出串，因为需要循环，所以将位次相加后与串的长度做模运算。
*/
void myShift_move(char *In,char *Out,int n,int s)
{
    int i=0;
    for(i=0; i<n; i++)
        *(Out+i)=*(In+(s+i)%n);
    *(Out+i)='\0';
}

/*
生成子密钥函数
参数：
K:64位的密钥
(*SK)[49]:得到的一轮子密钥
说明：输入64位密钥，进行PC1置换，之后进行16轮操作得到16个子密钥，每一轮对56位分成两部分，进行相应位数的移位操作，之后再拼接成56位进行PC2置换，得到该轮子密钥
*/
void mySubkey(char* K,char (*SK)[49])
{
    char out[57],C[57],D[29],e[29],t[57];
    int i=0,j=0;
    myPermutation(K,out,56,*PC_1);  //PC1置换
    strcpy(C,out);      //这里我们得到C0
    strcpy(D,out+28);   //这里我们得到D0
    for(j=0; j<16; j++)
    {
        myShift_move(C,e,28,ShiftMove_times[j]);  //循环左移
        strcpy(C,e);                   //这里我们得到Cj，j=1，2，3，4······
        myShift_move(D,e,28,ShiftMove_times[j]);
        strcpy(D,e);                   //这里我们得到Dj，j=1，2，3，4······
        strncpy(t, C, 28);
        strncpy(t+28, D, 28);
        myPermutation(t,*(SK+j),48,*PC_2);//PC2置换，得到Kj
    }
}

/*
轮函数lun
参数：
L: 第t轮的32位L
R: 第t轮的32位R
SK: 第t轮的48位子密钥
t: 轮数
说明：共进行16轮操作，每轮的32位R先进行拓展置换E变成48位,再与该轮子密钥异或，然后分成8组进行S盒代换。每组通过第1，6位组成的二进制串确定S盒行号，通过第2，3，4，5位确定列号，
找到对应的数并转为4位二进制串。8组代换拼接成32位为S盒代换结果，然后进行置换P。每轮经过S盒代换得到的结果与上一轮的L异或作为本轮的R，上一轮的R作为本轮的L。
*/
void mylun(char* L,char* R,char* SK,int t)
{
    int i=0,j=0;
    int row,col;
    char out1[49]= {0},out2[49]= {0},out3[33]= {0},out4[33]= {0},temp[33]= {0};
    printf("K%d=",t+1);
    puts(SK);   //输出本轮密钥
    myPermutation(R,out1,48,*E);  //将32位扩展成48位
    printf("E(R%d)=",t);
    puts(out1); //输出扩展后的R
    myXOR(out1,SK,48,out2); //将扩展后的R与子密钥异或
    printf("E(R%d)^K%d=",t,t+1);
    puts(out2); //输出异或后的结果
    for(i=0; i<8; i++)  //S盒代换，将每个48位分成8个6位的块，每一块经过一次S盒运算，由6位产生4位
    {
        row = ((out2[i*6]-'0')<<1)+(out2[i*6+5]-'0');   //第1，6位结合转换成十进制数组成行号
        col = ((out2[i*6+1]-'0')<<3)+((out2[i*6+2]-'0')<<2)+((out2[i*6+3]-'0')<<1)+(out2[i*6+4]-'0');  //第2，3，4，5位结合转换成十进制数组成列号
        for(j=3; j>=0; j--) //去对应的表中找对应的S盒中对应的行和列的数据
            *(out3+(i*4+3-j))=((S_Box[i][row*16+col]>>j)&1)+'0';  //将取到的S盒数据填到S盒输出的指定位置，先进行十进制转二进制
    }
    *(out3+32)='\0';    //结束标识
    printf("%d轮S盒输出=",t+1);
    puts(out3); //输出经过S盒运算后的结果
    myPermutation(out3,out4,32,*P);  //置换P
    printf("f(R%d,K%d)=",t,t+1);
    puts(out4);
    strcpy(temp,R);      //保存旧的R
    myXOR(L,out4,32,R);  //更新R
    printf("R%d=",t+1);
    puts(R);
    strcpy(L,temp);      //更新L
}


/*
加密函数：
说明：输入64位明文，先进行初始置换IP操作，接下来将置换输出的 64 位数据分成左右两半，左一半称为L0，
右一半称为R0各32位。然后进行16轮迭代，迭代完成后再经逆IP置换得到密文。
*/
char *encrypt(char* M,char* K)
{
    char out[65],L[33],R[33],SK[16][49],Cipher[65];
    int i=0;
    mySubkey(K,SK);                //产生16轮子密钥
    myPermutation(M,out,64,*IP);   //初始置换IP
    printf("\n\n-------------------------------加密过程-------------------------------\n\n");
    printf("原始的明文：");
    puts(M);
    printf("IP置换：");
    puts(out);
    strcpy(L,out);      //L0
    strcpy(R,out+32);   //R0
    for(i=0; i<16; i++)
    {
        printf("\n-------------------------------第%d轮------------------------------------\n",i+1);
        mylun(L,R,*(SK+i),i);   //轮函数迭代
    }
    strncpy(out, R, 32);   //L16 + R16
    strncpy(out+32, L, 32);
    myPermutation(out,Cipher,64,*C_IP);    //逆IP置换
    printf("\n加密后的密文：");
    puts(Cipher);
    char *CipherTmp = Cipher; //将char数组转换成指针数组
    return CipherTmp;   //因为C语言无法返回数组，所以我们返回一个指针数组
}

/*
解密函数：
说明：首先输入加密后的64位密文，然后进行IP置换，然后将置换输出的64为数据分成左右两部分，左一半为L0，
右一半为R0，各32位数据，然后进行16轮的倒迭代。迭代完成后进行IP逆置换即可得到解密后的密文。
*/
char *decrypt(char* MI,char* K){
    char out[65],L[33],R[33],SK[16][49],Ming[65];
    int i=0;
    mySubkey(K,SK);                //产生16轮子密钥
    myPermutation(MI,out,64,*IP);   //初始置换IP
    printf("\n\n-------------------------------解密过程-------------------------------\n\n");
    printf("传递来的密文：");
    puts(MI);
    printf("IP置换：");
    puts(out);
    strcpy(L,out);      //L0
    strcpy(R,out+32);   //R0
    for(i=15; i>=0; i--)
    {
        printf("\n-------------------------------第%d轮------------------------------------\n",i+1);
        mylun(L,R,*(SK+i),i);
    }
    strncpy(out, R, 32);   //L16 + R16
    strncpy(out+32, L, 32);
    myPermutation(out,Ming,64,*C_IP);    //逆IP置换
    printf("\n解密后的明文：");
    puts(Ming);
    char *MingTmp = Ming;   //将char数组转换成指针数组
    return MingTmp; //因为C语言无法返回数组，所以我们返回一个指针数组
}