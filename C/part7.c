#include <stdio.h>
#define MAX_N 1000
//输出质数
int prime_tab[MAX_N], prime_N;

int is_prime(int a){
    for (int i = 0; prime_tab[i] * prime_tab[i] <= a; ++i) {
        if(a % prime_tab[i]==0)
            return 0;
    }
    return 1;
}

void gen_primes(int max_n){
    prime_tab[0] = 2, prime_N = 1;
    for (int i = 3; i <= max_n; i+=2) {
        if(is_prime(i))
            prime_tab[prime_N++]=i;
    }
}

int main() {
    int num;
    printf("请输入要输出多少以内的质数：");
    scanf("%d",&num);
    gen_primes(num);
    for (int i = 0; i < prime_N; ++i) {
        printf("%d\n",prime_tab[i]);
    }
    return 0;
}

