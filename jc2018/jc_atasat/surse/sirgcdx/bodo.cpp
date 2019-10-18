//O(nlogn)-expected 100
//O(n) memorie
//Bogdan Pop
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int nmax=1000005;
const long long mod=1000*1000*1000+7;
bool b[nmax];
long long v[nmax];
long long fact[30],inv[30],combi[30];
long long curr,tot;
int n,i,j,k,x,ee,lg;
long long expo(long long A,int B)
{
    long long ret=1,p2=A;
    for(int p=0;p<=30;p++)
    {
        if(((1<<p)&B))
        {
            ret=(1LL*ret*p2)%mod;
        }
        p2=(1LL*p2*p2)%mod;
    }
    return ret;
}
void precalc_inv()
{
    fact[0]=1;
    for(long long I=1;I<=lg;I++)
        fact[I]=(1LL*fact[I-1]*I)%mod;
    inv[lg]=expo(fact[lg],mod-2);
    for(long long I=lg-1;I>=0;I--)
        inv[I]=(1LL*inv[I+1]*(I+1))%mod;
}
long long C(int A,int B)
{
    long long ret=1;
    for(long long I=A;I>=A-B+1;I--)
        ret=(1LL*ret*I)%mod;
    ret=(1LL*ret*inv[B])%mod;
    return ret;
}
void precalc_combi()
{
    //C(i,j-1)-ce valori iau puterile factorilor primi in afara de primul(de la 0 la i-1)
    //C(n-1,j-1)-unde se modifica puterile factorilor primi
    for(i=1;i<=lg;i++)
    {
        for(j=1;j<=min(n,i+1);j++)
            combi[i]=(1LL*combi[i]+1LL*C(i,j-1)*C(n-1,j-1))%mod;
    }
}
void ruleaza_ciur()
{
     for(i=2;i<=k;i++)
        if(!b[i])
           for(j=i;j<=k;j+=i)
              {
                  x=j;ee=0;b[j]=1;
                  while(x%i==0)
                    x/=i,ee++;
                  v[j]=(1LL*v[j]*combi[ee])%mod;
              }
}
int main()
{
    ifstream f("sirgcdx.in");
    ofstream g("sirgcdx.out");
    f>>n>>k;
    while(((1<<lg))<=k) lg++;
    for(i=1;i<=k;i++)
        v[i]=1;
    precalc_inv();
    precalc_combi();
    ruleaza_ciur();
    tot=0;
    for(i=1;i<=k;i++)
    {
        tot+=v[i];
        if(tot>=mod) tot-=mod;
    }
    g<<tot;
    return 0;
}