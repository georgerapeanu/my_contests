#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
 
FILE *fin = fopen("gordonramsay.in", "r"), *fout = fopen("gordonramsay.out", "w");
 
#define BUF_SIZE 1 << 17
 
int pos = BUF_SIZE;
char buf[BUF_SIZE];
 
inline char nextch() {
    if (pos == BUF_SIZE) fread(buf, BUF_SIZE, 1, fin), pos = 0;
    return buf[pos++];
}
 
inline int read() {
    char ch;
    while (!isdigit(ch = nextch()));
    int x = ch - '0';
    while (isdigit(ch = nextch())) x = 10 * x + ch - '0';
    return x;
}
 
#define MAXN 2000000
 
int u[MAXN + 1], v[MAXN + 1], sum[MAXN + 1];
long long rez[MAXN + 1];
std::vector < int > sol[MAXN + 1];
 
inline void solve(int n, int q, int cost, int profit, int rezistenta) {
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (v[i] == q);
 
    for (int i = 1; i <= n; i++) {
        int r = (n + i - 1) / i;
        u[0] = 0;
        for (int j = 0; j < n; j += i) {
            int x = sum[std::min(j + std::min(rezistenta, i), n)] - sum[j];
            if (x == 0)
                r--;
            else
                u[++u[0]] = x;
        }
 
        long long p = r - 1LL * cost * ((n + i - 1) / i) / profit;
        if (p > 0) {
            if (p > u[0])
                p = u[0];
            std::nth_element(u + 1, u + p, u + u[0] + 1);
            long long h = 1LL * u[p] * r * profit;
            for (int j = 1; j <= p; j++)
                h -= 1LL * (u[p] - u[j]) * profit;
 
            rez[i] += h - 1LL * cost * u[p] * ((n + i - 1) / i);
            sol[i].push_back(u[p]);
        } else
            sol[i].push_back(0);
    }
}
 
int main() {
    int n, k;
    fscanf(fin, "%d%d", &n, &k);
 
    if (n < 1 || n > MAXN || k < 1 || k > MAXN)
        return 1;
 
    if (1LL * n * k > MAXN)
        return 1;
 
    for (int i = 1; i <= n; i++) {
        fscanf(fin, "%d", &v[i]);
        if (v[i] < 1 || v[i] > k)
            return 1;
    }
 
    for (int i = 1; i <= k; i++) {
        int x, y, z, T = 1e9;
        fscanf(fin, "%d%d%d", &x, &y, &z);
        if (x < 1 || x > T || y < 1 || y > T || z < 1 || z > T)
            return 1;
        solve(n, i, x, y, z);
    }
 
    int ans = 1;
    for (int i = 2; i <= n; i++)
        if (rez[i] > rez[ans])
            ans = i;
 
    fprintf(fout, "%lld\n%d\n", rez[ans], ans);
    for (auto &x : sol[ans])
        fprintf(fout, "%d ", x);
 
    fclose(fin);
    fclose(fout);
    return 0;
}