#include <bits/stdc++.h>
#define MAXK 1000000
#define MOD 1000000007
#define MAXLOG 100
 
inline long long logpow(long long a, int n){
    long long p = 1;
    while(n){
        if(n % 2) p = (p * a) % MOD;
        a = a * a % MOD;
        n /= 2;
    }
    return p;
}
int ciur[1 + MAXK];
long long ans[1 + MAXK];
long long C[1 + MAXLOG];
std::pair <int, int> d[1 + MAXK];
 
int main(){
    FILE*fi,*fo;
    fi = fopen("sirgcdx.in","r");
    fo = fopen("sirgcdx.out","w");
 
    int n, k;
    fscanf(fi,"%d%d", &n, &k);
 
    C[0] = 1;
    for(int i = 1; i <= 25; i++){
        int inv = logpow(i, MOD - 2);
        C[i] = C[i - 1] * (n + i - 1) % MOD;
        C[i] = C[i] * inv % MOD;
    }
 
 
    for(int i = 1; i <= k; i++)
        ans[i] = 1;
 
    long long fin = 0;
    ciur[0] = ciur[1] = 1;
    for(int i = 1; i <= k; i++){
        if(!ciur[i]){
            d[1] = {i, 0};
            for(int j = i; j <= k; j += i){
                ciur[j] = 1;
                int cj = j / i;
                d[j] = {i, 1};
                if(d[cj].first == i)
                    d[j].second += d[cj].second;
                ans[j] = ans[j] * C[d[j].second] % MOD;
            }
        }
        fin = (fin + ans[i]) % MOD;
    }
    fprintf(fo,"%lld", fin);
 
    return 0;
}