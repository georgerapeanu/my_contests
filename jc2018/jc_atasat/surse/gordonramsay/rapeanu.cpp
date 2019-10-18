#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("gordonramsay.in","r");
FILE *g = fopen("gordonramsay.out","w");

int N,K;

int Cost[2000005];
int Prof[2000005];
int Rez[2000005];
int SP[2000005];
int V[2000005];
long long profit[2000005];
int num[2000005];
int X[2000005];

void build_SP_for(int alim){
    SP[0] = (V[0] == alim);
	for(int i = 1;i <= N;i++){
		SP[i] = SP[i - 1] + (V[i] == alim);
	}
}

long long solve(int alim,int t){
    num[0] = 0;
	int len = 0;
	for(int st = 0;st < N;st += t){
		num[++len] = SP[min(N,st + min(t,Rez[alim]) - 1)] - (st == 0 ? 0:SP[st - 1]);
	}

	int care = 0;
	while(care < len && 1LL * Prof[alim] * (len - care) - 1LL * Cost[alim] * len >= 0){
		care++;
	}

	nth_element(num,num + care,num + 1 + len);

	X[alim] = num[care];
	
	long long rez = - 1LL * Cost[alim] * len * num[care];
	for(int i = 0;i <= len;i++){
		rez += 1LL * Prof[alim] * min(num[care],num[i]);
	}
	return rez;
}

int main(){

	fscanf(f,"%d %d",&N,&K);

	for(int i = 0;i < N;i++){
		fscanf(f,"%d",&V[i]);
	}

	for(int i = 1;i <= K;i++){
		fscanf(f,"%d %d %d",&Cost[i],&Prof[i],&Rez[i]);
	}

	for(int i = 1;i <= K;i++){
		build_SP_for(i);
		for(int t = 1;t <= N;t++){
			profit[t] += solve(i,t);
		}
	}

	int t = 1;
	for(int i = 1;i <= N;i++){
		if(profit[i] > profit[t]){
			t = i;
		}
	}
	fprintf(g,"%lld\n%d\n",profit[t],t);
	
	for(int i = 1;i <= K;i++){
		build_SP_for(i);
		solve(i,t);
		fprintf(g,"%d ",X[i]);
	}
	

	fclose(f);
	fclose(g);

	return 0;
}
