#include <cstdio>
#include <algorithm>
 
FILE *fin = fopen("benzina.in", "r"), *fout = fopen("benzina.out", "w");
 
#define MAXN 100000
#define MAXP 530000
 
struct myc {
    int x, y;
    inline bool operator < (const myc &u) const {
        return x > u.x;
    }
} v[2 * MAXN + 1];
bool w;
int n, poz, aint[MAXP], lazy[MAXP];
 
inline void propag(int p) {
    if (lazy[p]) {
        aint[2 * p] += lazy[p];
        aint[2 * p + 1] += lazy[p];
        lazy[2 * p] += lazy[p];
        lazy[2 * p + 1] += lazy[p];
        lazy[p] = 0;
    }
}
 
void query(int p, int st, int dr) {
    if (poz <= st)
        w &= aint[p] > 1;
    else {
        propag(p);
        int m = (st + dr) / 2;
        if (poz <= m) query(2 * p, st, m);
        query(2 * p + 1, m + 1, dr);
    }
}
 
void update(int p, int st, int dr) {
    if (poz <= st)
        aint[p] -= 2, lazy[p] -= 2;
    else {
        ///propag(p);
        int m = (st + dr) / 2;
        if (poz <= m) update(2 * p, st, m);
        update(2 * p + 1, m + 1, dr);
        aint[p] = std::min(aint[2 * p], aint[2 * p + 1]);
    }
}
 
void dfs(int p, int st, int dr) {
    aint[p] = st;
    if (st < dr) {
        int m = (st + dr) / 2;
        dfs(2 * p, st, m);
        dfs(2 * p + 1, m + 1, dr);
    }
}
 
inline bool ok(int p) {
    w = 1;
    poz = p;
    query(1, 1, 2 * n);
    if (w)
        update(1, 1, 2 * n);
    return w;
}
 
int main() {
    fscanf(fin, "%d", &n);
 
    dfs(1, 1, 2 * n);
 
    long long ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        fscanf(fin, "%d", &v[i].x);
        v[i].y = i;
        ans += v[i].x;
    }
 
    for (int i = 1; i <= 2 * n; i++) {
        int x;
        fscanf(fin, "%d", &x);
        v[i].x = x - v[i].x;
    }
 
    std::sort(v + 1, v + 2 * n + 1);
 
    int p = 1, q = 0;
    while (p <= 2 * n && q < n) {
        if (ok(v[p].y)) {
            ans += v[p].x;
            q++;
        }
        p++;
    }
 
    if (q != n)
        return 1;
 
    fprintf(fout, "%lld\n", ans);
 
    fclose(fin);
    fclose(fout);
    return 0;
}