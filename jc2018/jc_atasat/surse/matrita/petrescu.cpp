#include <cstdio>
 
FILE *fin = fopen("matrita.in", "r"), *fout = fopen("matrita.out", "w");
 
#define MAXN 12000000
#define MAXP 800000
 
int n, MOD, phi[MAXN + 1], low[MAXN + 1], primes[MAXP];
 
inline int lgput(int a, long long n) {
    a %= MOD;
    int r = 1;
    while (n) {
        if (n % 2)
            r = 1LL * a * r % MOD;
        n /= 2;
        a = 1LL * a * a % MOD;
    }
    return r;
}
 
int main() {
    fscanf(fin, "%d%d", &n, &MOD);
 
    for (int i = 2; i <= n; i += 2)
        low[i] = 2;
    for (int i = 3; i <= n; i += 2) {
        if (low[i] == 0) {
            low[i] = i;
            primes[++primes[0]] = i;
        }
        for (int j = 1; j <= primes[0] && primes[j] <= low[i] && i * primes[j] <= n; j++)
            low[i * primes[j]] = primes[j];
    }
 
    for (int i = 2; i <= n; i++)
        if (low[i] == i)
            phi[i] = i - 1;
        else if (low[i] == low[i / low[i]])
            phi[i] = phi[i / low[i]] * low[i];
        else
            phi[i] = phi[i / low[i]] * (low[i] - 1);
 
    int ans = (n + 1) % MOD, last = 1;
    long long e = 0;
    for (int i = 2; i <= n; i++) {
        if (n / i + 1 == last)
            e += 2 * phi[i];
        else {
            ans = 1LL * ans * lgput(last, e) % MOD;
            e = 2 * phi[i];
            last = n / i + 1;
        }
    }
    ans = 1LL * ans * lgput(last, e) % MOD;
 
    ans--;
    if (ans < 0) ans += MOD;
    fprintf(fout, "%d\n", ans);
 
    fclose(fin);
    fclose(fout);
    return 0;
}