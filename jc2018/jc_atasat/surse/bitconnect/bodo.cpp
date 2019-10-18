#include <iostream>
#include <fstream>
#include <map>
#include <cassert>
using namespace std;
int ad[100][100];
int q[100],d[100];
map<long long,int> m;
int v[65];
long long i,j,p1,p2,p,u,x,y;
int tip,n,nr;
void add(long long x)
{
    nr=0;
    for(p1=0;p1<=63;p1++)
        if(((1LL<<p1)&x))
            v[++nr]=p1;
    for(i=1;i<=nr;i++)
        for(j=1;j<=nr;j++)
            ad[v[i]][v[j]]++;
}
void del(long long x)
{
    nr=0;
    for(p1=0;p1<=63;p1++)
        if(((1LL<<p1)&x))
            v[++nr]=p1;
    for(i=1;i<=nr;i++)
        for(j=1;j<=nr;j++)
            ad[v[i]][v[j]]--;
}
int despacito3(long long A,long long B)
{
    if(A==B) return 0;
    if((A&B)) return 1;
    u=0;
    for(p1=0;p1<=63;p1++)
    {
        d[p1]=0;
        if(((1LL<<p1)&A))
           {
               q[++u]=p1;
               d[p1]=1;
           }
    }
    for(p=1;p<=u;p++)
    {
        p1=q[p];
        for(i=0;i<=63;i++)
            if(ad[p1][i]&&(!d[i]))
        {
            d[i]=d[p1]+1;
            q[++u]=i;
            if(((1LL<<i)&B))
                return d[i];
        }
    }
    return -1;
}
int main()
{
    ifstream f("bitconnect.in");
    ofstream g("bitconnect.out");
    g<<"bit\n";
    f>>n;
    for(int ii=1;ii<=n;ii++)
    {
        f>>tip>>x;
        if(tip==1)
        {
            add(x);
        }
        if(tip==2)
        {
            del(x);
        }
        if(tip==3)
        {
            f>>y;
            g<<despacito3(x,y)<<'\n';
        }
    }
    return 0;
}