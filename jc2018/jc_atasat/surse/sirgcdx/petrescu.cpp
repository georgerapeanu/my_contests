#include <cstdio>
 
FILE *fin = fopen("sirgcdx.in", "r"), *fout = fopen("sirgcdx.out", "w");
 
#define MOD 1000000007
 
#define MAXU 30
#define MAXK 1000000
 
int n, k, ans, q[MAXU + 1], low[MAXK + 1];
 
inline int lgput(int a, int n) {
    int r = 1;
    while (n) {
        if (n % 2)
            r = 1LL * r * a % MOD;
        n /= 2;
        if (n)
            a = 1LL * a * a % MOD;
    }
    return r;
}
 
inline int comb(int n, int k) {
    if (n < k)
        return 0;
    int ans = 1;
    for (int i = n; i > n - k; i--)
        ans = 1LL * ans * i % MOD;
    for (int i = 1; i <= k; i++)
        ans = 1LL * ans * lgput(i, MOD - 2) % MOD;
    return ans;
}
 
inline void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}
 
inline int solve(int x) {
    if (low[x] == 0)
        low[x] = x;
    int ans = 1;
    while (x != 1) {
        int y = low[x], z = 1;
        x /= y;
        while (low[x] == y) {
            z++;
            x /= y;
        }
        ans = 1LL * ans * q[z] % MOD;
    }
    return ans;
}
 
int main() {
    fscanf(fin, "%d%d", &n, &k);
 
    for (int i = 1; i <= MAXU; i++)
        q[i] = comb(n + i - 1, i);
 
    for (int i = 2; i * i <= k; i++)
        if (low[i] == 0)
            for (int j = i * i; j <= k; j += i)
                if (low[j] == 0)
                    low[j] = i;
 
    int ans = 1;
    for (int i = 2; i <= k; i++)
        add(ans, solve(i));
    fprintf(fout, "%d\n", ans);
 
    fclose(fin);
    fclose(fout);
    return 0;
}