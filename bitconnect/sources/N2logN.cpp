///O(N^2logN)

#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

FILE *f = fopen("bitconnect.in","r");
FILE *g = fopen("bitconnect.out","w");

const int NMAX = 102000;
const int LGMAX = 62;
const int LEN = 1e4;

char buff[LEN];
int N;
int ind = LEN - 1;
map<long long,int> viz;
map<long long,int> Nodes;
map<long long,set<long long> > G;

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

long long Q[NMAX + 5];
int stq,drq;

int BFS(long long S,long long D){

    if(S == D){
        return 0;
    }

    viz.clear();

    stq = 1;drq = 0;
    Q[++drq] = S;
    viz[S] = 0;

    while(stq <= drq){
        long long node = Q[stq++];
        for(auto it:G[node]){
            if(!viz.count(it)){
                viz[it] = 1 + viz[node];
                Q[++drq] = it;
                if(it == D){
                    return viz[it];
                }
            }
        }
    }

    return -1;
}

void baga(long long x){
    for(auto it:Nodes){
        if(x & it.first){
            G[x].insert(it.first);
            G[it.first].insert(x);
        }
    }
    Nodes[x]++;
}

void scoate(long long x){
    for(auto it:Nodes){
        if(x & it.first){
            G[x].erase(it.first);
            G[it.first].erase(x);
        }
    }
    Nodes[x]--;
    if(!Nodes[x]){
        Nodes.erase(x);
    }
}

int main(){

    fprintf(g,"bit\n");

    N = i64();

    while(N--){
        int t;
		long long x,y;
        t = i64();
        if(t == 3){
            x = i64();
            y = i64();
            int ans = BFS(x,y);
            fprintf(g,"%d\n",ans);
        }
        else{
            x = i64();
            if(t == 1){
                baga(x);
            }
            else{
                scoate(x);
            }
        }
    }


    fclose(f);
    fclose(g);

    return 0;
}
