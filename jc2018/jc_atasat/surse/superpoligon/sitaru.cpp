/**
Bogdan Sitaru
O(N^2logN)
**/
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define FILE_IO
 
typedef long long LL;
typedef pair<int, int> pii;
 
class Integer {
public:
    //Pregateste clasa pentru interactiunea cu un modul - ii calculeaza phi-ul si descompunerea in factori primi
    static void prepare_MOD(int mod) {
        MOD = mod;
        phi = MOD;
        p_sz = 0;
        memset(p, 0, sizeof p);
        for (int i = 2; i * i <= mod; ++ i)
            if (mod % i == 0) {
                p[p_sz ++] = i;
                phi /= i;
                phi *= (i - 1);
 
                while (mod % i == 0)
                    mod /= i;
            }
 
        if (mod > 1) {
            p[p_sz ++] = mod;
            phi /= mod;
            phi *= (mod - 1);
            mod = 1;
        }
    }
 
    Integer() {
        memset(k, 0, sizeof k);
        val = 1;
    }
 
    Integer(const int &arg) {
        memset(k, 0, sizeof k);
        val = arg;
        for (int i = 0; i < p_sz; ++ i) {
            while (val % p[i] == 0) {
                val /= p[i];
                ++ k[i];
            }
        }
        val %= MOD;
    }
 
    Integer operator*(const Integer &arg) const {
        Integer ans;
        for (int i = 0; i < p_sz; ++ i)
            ans.k[i] = k[i] + arg.k[i];
        ans.val = (1LL * val * arg.val) % MOD;
        return ans;
    }
 
    Integer operator/(const Integer &arg) const {
        Integer ans;
        for (int i = 0; i < p_sz; ++ i)
            ans.k[i] = k[i] - arg.k[i];
        ans.val = (1LL * val * inv(arg.val)) % MOD;
        return ans;
    }
 
    //Returneaza numarul complet - cu tot cu factorii primi tinuti separat
    int to_int() {
        int ans = val;
        for (int i = 0; i < p_sz; ++ i)
            ans = (1LL * ans * expo(p[i], k[i])) % MOD;
        return ans;
    }
private:
    static const int FACTMAX = 9;
    static int MOD;
    static int phi;
    static int p[FACTMAX];
    static int p_sz;
 
    //Returneaza a ^ b prin exponentiere rapida
    static int expo(int a, int b) {
        if (!b)
            return 1 % MOD;
        else if (b & 1)
            return (1LL * expo(a, b - 1) * a) % MOD;
        else {
            int aux = expo(a, b >> 1);
            return (1LL * aux * aux) % MOD;
        }
    }
 
    //Returneaza inversul modular al lui x
    static int inv(int x) {
        return expo(x, phi - 1);
    }
 
    //X = (facts, val)
    int k[FACTMAX]; // = facts
    int val;
};
int Integer :: MOD;
int Integer :: phi;
int Integer :: p[FACTMAX];
int Integer :: p_sz;
 
pii v[1000005];
int N, K, mod;
int x[1005], y[1005];
int cnt[1005], sol[1005];
Integer inv[1005];
Integer arj[1005][1005];
int arjj[1005][1005];
 
int power(int x, int y)
{
    if(y <= 0)  return 1;
    int ans = power( (1LL * x * x) % mod, y >> 1 );
    if(y & 1)   ans = (1LL * ans * x) % mod;
    return ans;
}
 
int getphi(int N)
{
    int phi = N;
    int aux = N;
    for(int d = 2; d * d <= N; d++)
        if(aux % d == 0)
        {
            phi = (phi / d) * (d - 1);
            while(aux % d == 0) aux /= d;
        }
    if(aux != 1)
        phi = (phi / aux) * (aux - 1);
    return phi;
}
 
int main()
{
    #ifdef FILE_IO
    freopen("superpoligon.in", "r", stdin);
    freopen("superpoligon.out", "w", stdout);
    #endif
 
    scanf("%d%d%d", &N, &K, &mod);
 
    for (int i = 1; i <= N; i++)
        scanf("%d%d", &x[i], &y[i]);
 
    int M = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            v[++M] = {x[i] - x[j], y[i] - y[j]};
 
    sort(v + 1, v + M + 1);
 
    int nr = 1;
    for (int i = 2; i <= M; i++)
    {
        if (v[i] != v[i - 1])
        {
            cnt[nr]++;
            nr = 1;
        }
        else
            nr++;
    }
    cnt[nr]++;
 
    Integer::prepare_MOD(mod);
    Integer one(1);
 
    for(int i = 1; i <= N; i++)
        inv[i] = one / Integer(i);
 
    for(int i = 1; i <= N; i++)
    {
        arj[i][0] = one;
        for(int j = 1; j <= i; j++)
            arj[i][j] = arj[i][j - 1] * Integer(i - j + 1);
    }
 
    for(int i = 1; i <= N; i++)
        for(int j = 3; j <= i; j++)
        {
            arj[i][j] = arj[i][j] * inv[j];
            arjj[i][j] = arj[i][j].to_int();
        }
 
    for(int i = 3; i <= N; i++)
        for(int j = 3; j <= i && j <= K; j++)
            sol[j] = ((1LL * cnt[i] * arjj[i][j]) + sol[j]) % mod;
 
    for(int i = 3; i <= K; i++)
        printf("%d\n", sol[i]);
 
    return 0;
}