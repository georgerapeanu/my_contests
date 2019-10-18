#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("matrita.in","r");
FILE *g = fopen("matrita.out","w");

int phi[12000005];
bool is_composite[12000005];
vector<int> primes;
int N,MOD;

int lgpow(int b,long long e){
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

void sieve(int N){
	for(int i = 2;i <= N;i++){
        if(!is_composite[i]){
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for(int j = 0;j < (int)primes.size() && 1LL * i * primes[j] <= N;j++){
            is_composite[i * primes[j]] = 1;
            if(i % primes[j] == 0){
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            else{
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
            }
        }
	}
}

int main(){

    fscanf(f,"%d %d",&N,&MOD);
    int ans = 1;

	sieve(N);

	long long sum = 0;//hope it doesnt overflow
	int lim = 1;
	for(int i = 2;i <= N;i++){
		if(i > lim){
			ans = 1LL * ans * lgpow(N / (i - 1) + 1,2 * sum) % MOD;
			lim = N / (N / i);
			sum = 0;
		}
		sum += phi[i];
	}

    ans = 1LL * ans * lgpow(2,2 * sum) % MOD;
    ans = 1LL * ans * (N + 1) % MOD;
    ans = (ans == 0 ? MOD - 1:ans - 1);

    fprintf(g,"%d",ans);

    fclose(f);
    fclose(g);

    return 0;
}
