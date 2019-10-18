/**
Bogdan Sitaru
O(NlogN)
+
Assert
**/
#include <bits/stdc++.h>
 
using namespace std;
 
#define FILE_IO
 
typedef long long LL;
 
int N, M;
int a[100005], b[100005];
priority_queue<int> hp;
 
int main()
{
    #ifdef FILE_IO
    freopen("benzina.in", "r", stdin);
    freopen("benzina.out", "w", stdout);
    #endif
 
    /// Assert Subtask 4
 
    assert( scanf("%d", &N) == 1 );
    assert(1 <= N && N <= 50000);
    LL ans = 0LL;
    for(int i = 1; i <= 2 * N; i++)
    {
        assert( scanf("%d", &a[i]) == 1 );
        assert(0 <= a[i] && a[i] <= int(1e9));
    }
    for(int i = 1; i <= 2 * N; i++)
    {
        assert( scanf("%d", &b[i]) == 1 );
        assert(0 <= b[i] && b[i] <= int(1e9));
        ans += b[i];
    }
 
    for(int i = 1; i <= 2 * N; i++)
    {
        hp.push(a[i] - b[i]);
        if(i & 1)
        {
            ans += hp.top();
            hp.pop();
        }
    }
 
    printf("%lld\n", ans);
 
    return 0;
}