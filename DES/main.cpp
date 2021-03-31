#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <string.h>
#include"MyFun.h"   //自定义函数
using namespace std;


struct Data
{
    string str;
    string tmpbitstr;
    char M[65];
    char K[65];
    char *MI;
    char *Ming;
};



//将8位字符串转化为64bit
string StrToBitStr(string str)
{
    bitset<64> bstr ;
    for(int i=0;i<8;i++)
    {
        bitset<8> bits =  bitset<8>(str[i]);
        //cout<<str[i]<<endl;
        for(int j = 0;j<8;j++)
        {
            bstr[i*8+j] = bits[7-j];
        }
    }
    string s = bstr.to_string();
    //添加一个翻转操作
    reverse(begin(s),end(s));
    return s;
}


//将64bit二进制字符串转化为字符串
string BitStrToStr(string bstr)
{
    string str="";
    //每八位转化成十进制，然后将数字结果转化成字符
    int sum;
    for(int i=0;i<bstr.size();i+=8)
    {
        sum=0;
        for(int j=0;j<8;j++)
        if(bstr[i+j] == '1')
            sum = sum*2+1;
        else
            sum = sum*2;
        str =str+char(sum);
    }
    return str;
 
}


int main(){
    string str;
    string key;
    string tmpbitstr;
    string output;
    Data data;
    int num1,num2,j;
    cout<< "请输入要加密的字符:";
    getline(cin,str);
    cout<<"你输入的字符是:"<<str<<endl;
    cout<< "请输入8位字符的密钥:";
    getline(cin,key);
    string bkey = StrToBitStr(key);
    if(str.length()>8){
        num1 = ((str.length()/8)+1) * 8 - str.length();
        // cout<<num1<<endl;
        string tstr;
        for(int k =0;k<num1;k++){
            tstr += ' ';
        }
        // cout<<tstr<<endl;
        str += tstr;
        // cout<<str<<endl;
        // cout<<str.length()<<endl;

        num2 = str.length()/8;

        for (int i = 0;i<num2;i++){
            string tmpstr8;
            for(j=i*8;j< (8*i+8);j++){
                // if(j == 0){
                //     tmpstr8 += str[j];
                //     cout<<j<<str[j]<<endl;
                // }
                // if(j%8 !=0 && j > 0){
                // tmpstr8 += str[j];
                // cout<<j<<str[j]<<endl;
                tmpstr8 += str[j];
                // cout<<j<<str[j]<<endl;

            }
            string  bstr = StrToBitStr(tmpstr8);
            strcpy(data.M,bstr.c_str());
            strcpy(data.K,bkey.c_str());
            data.MI = encrypt(data.M,data.K);  //加密函数，并返回加密后的密文
            tmpbitstr = decrypt(data.MI,data.K);   //解密函数，并返回解密后的明文
                
            output += BitStrToStr(tmpbitstr);
        }
        cout<< "解密后的明文:";
        cout << output << endl;
        return 0;
    }else{
        string  bstr = StrToBitStr(str);
        strcpy(data.M,bstr.c_str());
        strcpy(data.K,bkey.c_str());
        data.MI = encrypt(data.M,data.K);  //加密函数，并返回加密后的密文
        tmpbitstr = decrypt(data.MI,data.K);   //解密函数，并返回解密后的明文

        output += BitStrToStr(tmpbitstr);
        cout<< "解密后的明文:";
        cout << output << endl;
        return 0;
    }


    // char M[65];
    // char K[65];
    // char *MI;
    // char *Ming;
    // strcpy(M,bstr.c_str());
    // strcpy(K,bkey.c_str());

    // cout<< "解密后的明文:";
    // cout << output << endl;
    // return 0;
}
