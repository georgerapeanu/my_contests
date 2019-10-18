/**
Bogdan Sitaru
O(N + sqrtN*logN)
**/
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define FILE_IO
 
int mod = 1e9 + 7;
 
int N, P, ans;
int phi[12000005];
int prime[6000005];
int primes[1000005];
 
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
    freopen("matrita.in", "r", stdin);
    freopen("matrita.out", "w", stdout);
    #endif
 
    scanf("%d", &N);
    scanf("%d", &mod);
    ans = N + 1;
 
    phi[2] = 1;
    for(int i = 3; i <= N; i++)
    {
        if(i & 1)
        {
            if(prime[i >> 1] == 0)
                primes[++P] = i, prime[i >> 1] = i;
            for(int j = 1; j <= P && primes[j] <= prime[i >> 1] && i * primes[j] <= N; j++)
                prime[ (i * primes[j]) >> 1 ] = primes[j];
 
            if(prime[i >> 1] == i)  phi[i] = i - 1;
            else if(prime[(i / prime[i >> 1]) >> 1] == prime[i >> 1])
                phi[i] = phi[i / prime[i >> 1]] * prime[i >> 1];
            else
                phi[i] = phi[i / prime[i >> 1]] * (prime[i >> 1] - 1);
        }
        else
        {
            if((i >> 1) & 1)    phi[i] = phi[i >> 1];
            else    phi[i] = phi[i >> 1] << 1;
        }
    }
 
    int lst = -1;
    int e = 0;
    for(int i = 1; i <= N; i++)
    {
        int val = (N / i + 1);
        if(val == lst)  e = (e + 2 * phi[i]) % (mod - 1);
        else
        {
            ans = (1LL * ans * power(lst, e)) % mod;
            lst = val;
            e = 2 * phi[i];
        }
    }
    ans = (1LL * ans * power(lst, e)) % mod;
    ans = (ans - 1 + mod) % mod;
    printf("%d\n", ans);
 
    return 0;
}