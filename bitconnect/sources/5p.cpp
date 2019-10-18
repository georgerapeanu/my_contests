///5p

#include <cstdio>

using namespace std;

FILE *f = fopen("bitconnect.in","r");
///FILE *g1 = fopen("bitconnect.out","w");
FILE *g2 = fopen("bitconnect.out","w");

int N;

int main(){

 ///   fprintf(g1,"bit\n");
    fprintf(g2,"connect\n");

    fscanf(f,"%d",&N);

    while(N--){
        int t;
		long long x,y;
        fscanf(f,"%d",&t);
        if(t == 3){
            fscanf(f,"%lld %lld",&x,&y);
            ///bit Mode
            if(x == y){
    //            fprintf(g1,"0\n");
            }
            else if(x & y){
      //          fprintf(g1,"1\n");
            }
            else{
        //        fprintf(g1,"-1\n");
            }

            ///connect Mode
            if(x & y){
                fprintf(g2,"1\n");
            }
            else{
                fprintf(g2,"0\n");
            }
        }
        else{
            fscanf(f,"%lld",&x);
        }
    }

    fclose(f);
    ///fclose(g1);
	fclose(g2);

    return 0;
}
