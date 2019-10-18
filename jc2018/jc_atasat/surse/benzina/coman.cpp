#include <bits/stdc++.h>
#define MAXN 50000
 
std::priority_queue <std::pair <int, int>> pq;
int a[1 + 2 * MAXN], b[1 + 2 * MAXN];
int main(){
    FILE*fi,*fo;
    fi = fopen("benzina.in","r");
    fo = fopen("benzina.out","w");
 
    int n;
    fscanf(fi,"%d", &n);
    for(int i = 1; i <= 2 * n; i++) fscanf(fi,"%d", &a[i]);
    for(int i = 1; i <= 2 * n; i++) fscanf(fi,"%d", &b[i]);
 
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        if(!pq.empty() && a[2 * i - 1] - b[2 * i - 1] < pq.top().first){
            ans += pq.top().first + b[2 * i - 1];
            pq.pop();
            pq.push({a[2 * i - 1] - b[2 * i - 1], 2 * i - 1});
        }
        else ans += a[2 * i - 1];
 
        ans += b[2 * i];
        pq.push({a[2 * i] - b[2 * i], 2 * i});
    }
    fprintf(fo,"%lld", ans);
 
    return 0;
}