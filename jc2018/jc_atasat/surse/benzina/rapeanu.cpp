#include <cstdio>
#include <queue>

using namespace std;

FILE *f = fopen("benzina.in","r");
FILE *g = fopen("benzina.out","w");

int N;
int A[100005];
int B[100005];
long long best;
priority_queue<int> H;

int main(){
	fscanf(f,"%d",&N);
	N *= 2;
	for(int i = 1;i <= N;i++){
		fscanf(f,"%d",&A[i]);
	}
	for(int i = 1;i <= N;i++){
		fscanf(f,"%d",&B[i]);
		best += B[i];
	}
	
	for(int i = 1;i <= N;i++){
		H.push(A[i] - B[i]);
		if(i & 1){
			best += H.top();
			H.pop();
		}
	}
	
	fprintf(g,"%lld",best);
	
	fclose(f);
	fclose(g);
	
	return 0;
}