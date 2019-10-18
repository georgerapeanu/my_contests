///solutie oficiala O(N + sqrt(N) * log(N))
#include <bits/stdc++.h>
#define MAXN 12000000
 
long long MOD;
int ciur[1 + MAXN / 2 + 1];
int phi[1 + MAXN];
int prime[800000], ind;
 
inline int logpow(int a, long long n){
    int p = 1;
    while(n){
        if(n % 2) p = (1LL * p * a) % MOD;
        a = (1LL * a * a) % MOD;
        n /= 2;
    }
    return p;
}
 
int main(){
    FILE*fi,*fo;
    fi = fopen("matrita.in","r");
    fo = fopen("matrita.out","w");
 
    int n;
    fscanf(fi,"%d%lld", &n, &MOD);
 
    int val = n + 1, lim = 1;
    long long exp = 0, ans = 1;
    phi[2] = 1, prime[++ind] = 2;
    for(int i = 2; i <= n; i++){
        if(i % 2){
            if(!ciur[i / 2 + 1]){
                prime[++ind] = i;
                ciur[i / 2 + 1] = i;
                phi[i] = i - 1;
            }
 
            int j;
            for(j = 1; j <= ind && i * prime[j] <= n && prime[j] < ciur[i / 2 + 1]; j++){
                if(prime[j] != 2) ciur[i * prime[j] / 2 + 1] = prime[j];
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
            if(j <= ind && i * prime[j] <= n && prime[j] == ciur[i / 2 + 1]){
                ciur[i * prime[j] / 2 + 1] = prime[j];
                phi[i * prime[j]] = phi[i] * prime[j];
            }
        }
        else if(2 * i <= n)
            phi[i * 2] = phi[i] * 2;
 
        if(i > lim){
            ans = (ans * logpow(val, exp)) % MOD;
            val = n / i, lim = n / val;
            val++, exp = 0;
        }
        exp += phi[i];
    }
    ans = (ans * logpow(val, exp)) % MOD;
    fprintf(fo,"%lld", ((ans * ans) % MOD * (n + 1) % MOD - 1 + MOD) % MOD);
 
    return 0;
}