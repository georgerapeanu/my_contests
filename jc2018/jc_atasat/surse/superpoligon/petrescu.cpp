#include <cstdio>
#include <algorithm>
#include <map>
 
FILE *fin = fopen("superpoligon.in", "r"), *fout = fopen("superpoligon.out", "w");
 
#define MAXN 1000
 
std::map < long long , int > mp;
int x[MAXN], y[MAXN], MOD;
int rez[MAXN + 1], ans[MAXN + 1];
int fact[MAXN + 1], comb[MAXN + 1][MAXN + 1];
 
int main() {
    int n, k;
    fscanf(fin, "%d%d%d", &n, &k, &MOD);
 
    for (int i = 0; i < n; i++)
        fscanf(fin, "%d%d", &x[i], &y[i]);
 
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mp[((1LL * (x[i] - x[j])) << 32) + y[i] - y[j]]++;
 
    for (auto &x : mp)
        rez[x.second]++;
 
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = 1LL * fact[i - 1] * i % MOD;
 
    for (int i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
    }
 
    for (int i = 3; i <= n; i++)
        if (rez[i])
            for (int j = 3; j <= k && j <= i; j++)
                ans[j] = (ans[j] + 1LL * rez[i] * fact[j - 1] % MOD * comb[i][j]) % MOD;
 
    for (int i = 3; i <= k; i++)
        fprintf(fout, "%d\n", ans[i]);
 
    fclose(fin);
    fclose(fout);
    return 0;
}