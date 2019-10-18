#include <cstdio>
#include <cstdlib>
#include <cctype>
 
FILE *fin = fopen("bitconnect.in", "r"), *fout = fopen("bitconnect.out", "w");
 
#define BUF_SIZE 1 << 17
 
int pos = BUF_SIZE;
char buf[BUF_SIZE];
 
inline char nextch() {
    if (pos == BUF_SIZE) fread(buf, BUF_SIZE, 1, fin), pos = 0;
    return buf[pos++];
}
 
inline long long read() {
    char ch;
    while (!isdigit(ch = nextch()));
    long long x = ch - '0';
    while (isdigit(ch = nextch())) x = 10 * x + ch - '0';
    return x;
}
 
int m[62][62], v[63], q[62], d[62];
 
inline void baga(int t) {
    long long x = read();
 
    v[0] = 0;
    for (int i = 0; i < 62; i++)
        if ((1LL << i) & x)
            v[++v[0]] = i;
    for (int i = 1; i <= v[0]; i++)
        for (int j = 1; j <= v[0]; j++)
            if (t == 1)
                m[v[i]][v[j]]++;
            else
                m[v[i]][v[j]]--;
}
 
inline int query() {
    long long x = read();
    long long y = read();
 
    if (x == y)
        return 0;
 
    int st = 0, dr = 0;
    for (int i = 0; i < 62; i++) {
        if ((1LL << i) & x) {
            d[i] = 1;
            q[dr++] = i;
            if (y & (1LL << i))
                return 1;
        } else
            d[i] = -1;
    }
 
    while (st < dr) {
        for (int i = 0; i < 62; i++) {
            if (d[i] == -1 && m[q[st]][i]) {
                q[dr++] = i;
                d[i] = d[q[st]] + 1;
                if (y & (1LL << i))
                    return d[i];
            }
        }
        st++;
    }
 
    return -1;
}
 
inline void solve() {
    int t = read();
 
    if (t <= 2)
        baga(t);
    else
        fprintf(fout, "%d\n", query());
}
 
int main() {
    fprintf(fout, "bit\n");
 
    for (int t = read(); t; t--)
        solve();
 
    fclose(fin);
    fclose(fout);
    return 0;
}