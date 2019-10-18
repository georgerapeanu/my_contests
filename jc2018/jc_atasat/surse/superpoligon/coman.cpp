#include <bits/stdc++.h>
#define MAXN 1009
#define MOD 666811
 
int n, k;
long long m;
int ans[1 + MAXN], f[1 + MAXN];
struct Point{int x, y;} v[1 + MAXN];
 
class Hash{
    public:
    int k = 0, next[MAXN * MAXN + 1], lista[MOD];
    std::pair <int, int> val[MAXN * MAXN + 1];
    int d[MAXN * MAXN + 1];
    inline void insert(std::pair <int, int> element){
        k++;
        val[k] = element;
        d[k] = 1;
        next[k] = lista[(element.second * 11 + element.first) % MOD];
        lista[(element.second * 11 + element.first) % MOD] = k;
    }
    inline int find(std::pair <int, int> element){
        int p = lista[(element.second * 11 + element.first) % MOD];
        while(p != 0 && val[p] != element)
            p = next[p];
        return p;
    }
} H;
 
int C[1 + MAXN][1 + MAXN];
int fact[1 + MAXN];
 
int main(){
    FILE*fi,*fo;
    fi = fopen("superpoligon.in","r");
    fo = fopen("superpoligon.out","w");
 
    fscanf(fi,"%d%d%lld", &n, &k, &m);
    for(int i = 1; i <= n; i++)
        fscanf(fi,"%d%d", &v[i].x, &v[i].y);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            std::pair <int, int> tmp = {v[j].x - v[i].x, v[j].y - v[i].y};
            if(!H.find(tmp)){
                H.insert(tmp);
                f[1]++;
            }
            else{
                H.d[H.find(tmp)]++;
                int x = H.d[H.find(tmp)];
                f[x]++, f[x - 1]--;
            }
        }
 
    fact[0] = 1, C[0][0] = 1;
    for(int i = 1; i <= n; i++){
        fact[i] = (1LL * fact[i - 1] * i) % m;
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % m;
    }
 
    for(int i = 1; i <= n; i++)
        if(f[i])
            for(int j = 3; j <= k && j <= i; j++)
                ans[j] = (1LL * ans[j] + (1LL * f[i] * C[i][j] % m) * fact[j - 1]) % m;
    for(int i = 3; i <= k; i++)
        fprintf(fo,"%d\n", ans[i]);
 
    return 0;
}