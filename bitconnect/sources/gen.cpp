///O(Nlog^2N)
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
 
using namespace std;
 
FILE *f = fopen("grader_test5.in","r");
FILE *g = fopen("grader_test5.ok","w");
 
const int NMAX = 102000;
const int LGMAX = 62;///bitii sunt de la 0 la LGMAX -1
const int LEN = 1e5;
 
char buff[LEN];
int ind = LEN - 1;
 
long long i64(){
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
 
    long long rez = 0;
 
    while(buff[ind] >= '0' && buff[ind] <= '9'){
        rez = rez * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}
 
int N;
 
int viz[LGMAX];
int Q[LGMAX + 5];
int stq,drq;
 
int how_many[LGMAX][LGMAX];
 
int bits[LGMAX + 5];
int num = 0;
 
void baga(long long val,int op){
	num = 0;
    for(int bit = 0;bit < LGMAX;bit++){
		if((val >> bit) & 1){
			bits[++num] = bit;
		}
	}
    for(int bit = 1;bit <= num;bit++){
		for(int next_bit = 1;next_bit <= num;next_bit++){
			how_many[bits[bit]][bits[next_bit]] += op;
		}
    }
}
 
int BFS(long long x,long long y){
 
    if(x == y){
        return 0;
    }
 
    stq = 1;drq = 0;
    memset(viz,0,sizeof(viz));
 
    for(int bit = 0;bit < LGMAX;bit++){
        if((x >> bit) & 1){
            viz[bit] = 1;
            Q[++drq] = bit;
            if((y >> bit) & 1){
                return 1;
            }
        }
    }
 
    while(stq <= drq){
        int bit = Q[stq++];
        for(int next_bit = 0;next_bit < LGMAX;next_bit++){
            if(!viz[next_bit] && how_many[bit][next_bit]){
                viz[next_bit] = 1 + viz[bit];
                Q[++drq] = next_bit;
                if((y >> next_bit) & 1){
                    return viz[next_bit];
                }
            }
        }
    }
    return -1;
}
 
int main(){
 
    fprintf(g,"bit\n");
 
 
    N = i64();
    while(N--){
        int t;
        long long x,y;
        t = i64();
        x = i64();
        if(t == 3){
            y = i64();
            int ans = BFS(x,y);
            fprintf(g,"%d\n",ans);
        }
        else{
            baga(x,(t == 1 ? 1 : -1));
        }
    }
 
    fclose(f);
    fclose(g);
 
    return 0;
}