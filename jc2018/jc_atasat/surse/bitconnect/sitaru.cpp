/**
Bogdan Sitaru
O(Q * log^2VMAX)
**/
#include <bits/stdc++.h>
 
using namespace std;
 
#define FILE_IO
 
typedef long long LL;
 
int B, bts[70];
int cnt[70][70];
int d[70];
queue<int> q;
 
template<typename T>
T parse()
{
    char ch = getchar();
    while(ch < '0' || '9' < ch) ch = getchar();
    T val = T(0);
    while('0' <= ch && ch <= '9')
    {
        val = val * 10 + ch - '0';
        ch = getchar();
    }
    return val;
}
 
int N, nr[25];
void print(int x)
{
    if(x == 0)  { putchar('0'); return; }
    if(x < 0)   { putchar('-'); x = -x; }
 
    N = 0;
    while(x > 0)
    {
        nr[++N] = x % 10;
        x /= 10;
    }
    while(N > 0)
        putchar('0' + nr[N]), N--;
}
 
void add_value(LL x, int val = 1)
{
    B = 0;
    for(int i = 0; i < 62; i++)
        if( (x >> i) & 1 )
            bts[++B] = i;
    for(int i = 1; i <= B; i++)
        for(int j = i + 1; j <= B; j++)
            cnt[ bts[i] ][ bts[j] ] += val, cnt[ bts[j] ][ bts[i] ] += val;
}
 
int query(LL x, LL y)
{
    if(x == y)  return 0;
    if((x & y)) return 1;
    while(!q.empty())   q.pop();
 
    for(int i = 0; i < 62; i++)
        if( (x >> i) & 1 )
            d[i] = 0, q.push(i);
        else
            d[i] = 70;
 
    while(!q.empty())
    {
        int b = q.front();
        q.pop();
 
        for(int i = 0; i < 62; i++)
            if(cnt[b][i] > 0 && d[i] > d[b] + 1)
            {
                d[i] = d[b] + 1;
                if( (y >> i) & 1 )  return (d[i] + 1);
                q.push(i);
            }
    }
    return -1;
}
 
int main()
{
    #ifdef FILE_IO
    freopen("bitconnect.in", "r", stdin);
    freopen("bitconnect.out", "w", stdout);
    #endif
 
    printf("bit\n");
 
    int Q;
    //scanf("%d", &Q);
    Q = parse<int>();
 
    for(int q = 1; q <= Q; q++)
    {
        int op;
        //scanf("%d", &op);
        op = parse<int>();
        if(op == 1 || op == 2) /// Insert / Erase
        {
            LL x;
            //scanf("%lld", &x);
            x = parse<LL>();
            add_value(x, (op == 1 ? 1 : -1));
        }
        else    /// Query
        {
            LL x, y;
            //scanf("%lld%lld", &x, &y);
            x = parse<LL>(), y = parse<LL>();
            int ans = query(x, y);
            //printf("%d\n", ans);
            print(ans), putchar('\n');
        }
    }
 
    return 0;
}