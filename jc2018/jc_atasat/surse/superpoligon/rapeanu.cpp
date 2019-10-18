#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("superpoligon.in","r");
FILE *g = fopen("superpoligon.out","w");

int MOD;
int N,K;
int X[1005],Y[1005];
pair<int,int> V[1000 * 1000 + 5];
int C[1005][1005];
int fact[1005];
int ans[1005];

int main(){
	
	fscanf(f,"%d %d %d",&N,&K,&MOD);
	
	for(int i = 0;i <= N;i++){
		fact[i] = (i == 0 ? 1 : 1LL * fact[i - 1] * i % MOD);
		C[i][0] = 1;
		for(int j = 1; j <= i;j++){
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			if(C[i][j] >= MOD){
				C[i][j] -= MOD;
			}
		}
	}
	
	for(int i = 1;i <= N;i++){
		fscanf(f,"%d %d",&X[i],&Y[i]);
	}
	
	int len = 0;
	
	for(int i = 1;i <= N;i++){
		for(int j = 1;j <= N;j++){
			V[++len] =  {X[j] - X[i],Y[j] - Y[i]};
		}
	}
	
	sort(V + 1,V + 1 + len);
	
	int num = 0;
	for(int i = 1;i <= len;i++){
		if(V[i] != V[i - 1]){
			for(int j = 3;j <= num && j <= K;j++){
				ans[j] = (ans[j] + 1LL * C[num][j] * fact[j - 1]) % MOD;
			}
			num = 0;
		}
		num++;
	}
	
	for(int i = 3;i <= K;i++){
		fprintf(g,"%d\n",ans[i]);
	}
	
	fclose(f);
	fclose(g);
	return 0;
}