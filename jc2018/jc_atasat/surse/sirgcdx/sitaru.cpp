/**
Bogdan Sitaru
O(KlogK)
**/
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define FILE_IO
 
typedef pair<int, int> pii;
 
const int mod = 1e9 + 7;
const int M = 20;
 
int N, K, ans;
int cmb[25], f[25], coef[25];
int prime[1000005], cnt[1000005], same[1000005];
int dp[1000005][25];
 
vector<int> solve, primes;
vector<pii> hashes;
unordered_map<int, int> mp;
 
int add(int x, int y) { x += y; if(x >= mod) x -= mod; return x; }
int mul(int x, int y) { return (1LL * x * y) % mod; }
 
int power(int x, int y)
{
    if(y <= 0)  return 1;
    int ans = power( (1LL * x * x) % mod, y >> 1 );
    if(y & 1)   ans = (1LL * ans * x) % mod;
    return ans;
}
 
int main()
{
    #ifdef FILE_IO
    freopen("sirgcdx.in", "r", stdin);
    freopen("sirgcdx.out", "w", stdout);
    #endif
 
    scanf("%d%d", &N, &K);
 
    for(int i = 2; i * i <= K; i++)
        if(prime[i] == 0)
        {
            prime[i] = i;
            for(int j = i * i; j <= K; j += i)
                if(!prime[j])
                    prime[j] = i;
        }
    for(int i = 2; i <= K; i++)
        if(prime[i] == 0)   prime[i] = i;
 
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uid(1, 1e6);
    for(int i = 1; i < M; i++)  coef[i] = uid(gen);
 
    for(int i = 2; i <= K; i++)
    {
        for(int j = 1; j < M; j++)  f[j] = 0;
 
        int aux = i;
        while(aux > 1)
        {
            int ee = 0;
            int p = prime[aux];
            while(aux % p == 0)
            {
                ee++;
                aux /= p;
            }
            f[ee]++;
        }
 
        int hsh = 0;
        for(int j = 1; j < M; j++)  hsh = add(hsh, mul(coef[j], f[j]));
 
        int p = 0;
        int u = int(hashes.size()) - 1;
        int pos = hashes.size();
        while(p <= u)
        {
            int mij = p + (u - p) / 2;
            if(hashes[mij].first >= hsh)
            {
                pos = mij;
                u = mij - 1;
            }
            else
                p = mij + 1;
        }
 
        if(pos < hashes.size() && hashes[pos].first == hsh)
        {
            same[i] = hashes[pos].second;
            cnt[ same[i] ]++;
        }
        else
        {
            hashes.insert(hashes.begin() + pos, {hsh, i});
            same[i] = i;
            cnt[i] = 1;
            solve.push_back(i);
        }
    }
 
    cmb[0] = 1;
    for(int i = 1; i <= M; i++)
        cmb[i] = mul(cmb[i - 1], mul(N - i, power(i, mod - 2)));
 
    ans = 1;
    dp[1][1] = 1;
    same[1] = 1;
    for(auto &x: solve)
    {
        int aux = x;
        dp[x][1] = dp[x][2] = 1;
        for(int i = 2; i * i <= x; i++)
            if(x % i == 0)
            {
                for(int j = 1; j < M; j++)
                    dp[x][j + 1] = add(dp[x][j + 1], dp[ same[x / i] ][j]);
                if(i != x / i)
                    for(int j = 1; j < M; j++)
                        dp[x][j + 1] = add(dp[x][j + 1], dp[ same[i] ][j]);
            }
 
        for(int i = 1; i <= M; i++)
            ans = add( ans, mul(cnt[x], mul(cmb[i - 1], dp[x][i])) );
    }
 
    printf("%d\n", ans);
 
    return 0;
}