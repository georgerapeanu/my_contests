#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("sirgcdx.in","r");
FILE *g = fopen("sirgcdx.out","w");

const int MOD = (1e9) + 7;
int N,K;
bool E[1000005];
int lg[10000005];
int rez[10000005];
int C[25];
int ifact[25];

int lgpow(int b,int e){
	int p = 1;
	while(e){
		if(e & 1){
			p = 1LL * p * b % MOD;
		}
		b = 1LL * b * b % MOD;
		e >>= 1;
	}
	return p;
}

int Comb(int N,int K){
	int rez = 1;
	for(int i = N - K + 1;i <= N;i++){
		rez = 1LL * rez * i % MOD;
	}
	rez = 1LL * rez * ifact[K] % MOD;
	return rez;
}

int main(){
	
	ifact[0] = 1;
	for(int i = 1;i <= 24;i++){
		ifact[i] = 1LL * ifact[i - 1] * i % MOD;
	}
	
	ifact[24] = lgpow(ifact[24],MOD - 2);
	
	for(int i = 23;i >= 0;i--){
		ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
	}
	
	fscanf(f,"%d %d",&N,&K);
	
	for(int i = 0;i <= 24;i++){
		C[i] = Comb(N + i - 1,i);
	}
	
	E[0] = E[1] = 1;
	for(int i = 2;i <= K;i++){
		if(!E[i]){
			for(int j = i * 2;j <= K;j += i){
				E[j] = 1;
			}
		}
	}
	
	for(int i = 1;i <= K;i++){
		rez[i] = 1;
	}
	
	for(int i = 2;i <= K;i++){
		if(!E[i]){
			int num = 1;
			for(int j = i;j <= K;j += i,num++){
				lg[j] = 1 + lg[num];
				rez[j] = 1LL * rez[j] * C[lg[j]] % MOD;
			}
			for(int j = 1;j < num;j++){
				lg[j] = 0;
			}
		}
	}
	
	int ans = 0;
	
	for(int i = 1;i <= K;i++){
		ans += rez[i];
		if(ans >= MOD){
			ans -= MOD;
		}
	}
	
	fprintf(g,"%d",ans);
	
	fclose(f);
	fclose(g);
	
	return 0;
}