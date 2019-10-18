#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
//Bodo-100
using namespace std;
const int nmax=2*1000*1000+5;
string s;
int rezi[nmax],pr[nmax],cost[nmax],sum[nmax],v[nmax],arr[nmax];
int n,i,j,nr,t,opti,cap,al,k,num,ch,care;
long long fin[nmax];
long long loc,mx,won;
ifstream f("gordonramsay.in");
ofstream g("gordonramsay.out");
void get_local_opt()
{
    loc=nr=won=0;
    if(rezi[al]<i) cap=rezi[al]-1;
    else cap=i-1;
    v[0]=0;opti=0;
    for(j=1;j<=n;j+=i)
        v[++nr]=sum[min(j+cap,n)]-sum[j-1];
    care=0;
    while(1LL*(nr-care)*pr[al]-1LL*nr*cost[al]>0)
        care++;
    nth_element(v,v+care,v+nr+1);
    for(j=0;j<=nr;j++)
       loc+=1LL*min(v[j],v[care]);
    loc=1LL*loc*pr[al];
    loc-=1LL*v[care]*nr*cost[al];
    fin[i]+=loc;opti=v[care];
}
void calc_opt()
{
    for(al=1;al<=k;al++)
    {
        for(i=1;i<=n;i++)
            sum[i]=sum[i-1]+(arr[i]==al);
        for(i=1;i<=n;i++)
         get_local_opt();
    }
}
void reco()
{
    for(i=1;i<=n;i++)
        if(fin[i]>fin[mx])
          mx=i;
    i=mx;
    g<<fin[i]<<'\n';
    g<<i<<'\n';
    for(al=1;al<=k;al++)
    {
        opti=0;
        for(j=1;j<=n;j++)
            sum[j]=sum[j-1]+(arr[j]==al);
        get_local_opt();
        g<<opti<<' ';
    }
}
int getnum()
{
    num=0;
    while(s[ch]>='0'&&s[ch]<='9')
    {
        num=num*10+s[ch]-'0';
        ch++;
    }
    ch++;
    return num;
}
int main()
{
      f>>n>>k;
    getline(f,s);
    getline(f,s);ch=0;
    for(i=1;i<=n;i++)
    {
        arr[i]=getnum();
    }
    for(i=1;i<=k;i++)
    {
        getline(f,s);ch=0;
        cost[i]=getnum();pr[i]=getnum();rezi[i]=getnum();
    }
    calc_opt();
    reco();
    return 0;
}