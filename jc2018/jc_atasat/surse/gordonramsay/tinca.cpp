#include <bits/stdc++.h>
 
/*
 
Solutie gordon
Complexitate in timp: O(N*K*log^2)
CU PARSARE
 
*/
 
class InParser {
private:
    FILE *fin;
    char *buff;
    int sp;
  
    char read_ch() {
        ++sp;
        if (sp == 4096) {
            sp = 0;
            fread(buff, 1, 4096, fin);
        }
        return buff[sp];
    }
  
public:
    InParser(const char* nume) {
        fin = fopen(nume, "r");
        buff = new char[4096]();
        sp = 4095;
    }
      
    InParser& operator >> (int &n) {
        char c;
        while (!isdigit(c = read_ch()) && c != '-');
        int sgn = 1;
        if (c == '-') {
            n = 0;
            sgn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = read_ch())) {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }
      
    InParser& operator >> (long long &n) {
        char c;
        n = 0;
        while (!isdigit(c = read_ch()) && c != '-');
        long long sgn = 1;
        if (c == '-') {
            n = 0;
            sgn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = read_ch())) {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }
} fin("gordonramsay.in");
 
using namespace std;
 
// Restrictiile problemei
const int MAX_N = 1000000;
const int MAX_K = 1000000;
 
// Comenzile noastre
int comenzi[MAX_N];
 
// Caracteristicile fiecarui aliment
int cost[MAX_K], profit[MAX_K], rezist[MAX_K];
 
// Pentru fiecare bucket vedem cate alimente putem satisface
int bucks[MAX_N + 1];
 
// Smenul lui Mars pentru fiecare aliment
// Ca sa aflam in O(1) cate alimente de un fel sunt intr-un interval
int **smen;
 
// Ne returneaza smenul lui Mars chiar si daca n-ul e in afara
static inline int getSmen(int k, int n, int maxn) {
  if (n < 0)
    return 0;
  return smen[k][min(maxn - 1, n)];
}
 
// Numarul de alimente din fiecare tip
int lim[MAX_K];
 
// Solutia problemei
int trez;
int xrez[MAX_K];
 
// Profitul maxim scos
long long best;
 
// X-uri intermediare
int xint[MAX_K];
 
int main() {
  // N si K din problema
  int n, k;
 
  // Fisierele din problema
  FILE *fout = fopen("gordonramsay.out", "w");
   
  // Citim alimentele
  fin >> n >> k;
 
  // Ne alocam dinamic o matrice
  smen = new int*[k];
  for(int i = 0; i < k; ++i)
    smen[i] = new int[n];
 
  for (int i = 0; i < n; ++i) {
    fin >> comenzi[i];
     
    // Decrementam comenzile ca sa fie indexate de la 0
    --comenzi[i];
     
    // Calculam frecventele pt fiecare aliment
    lim[comenzi[i]]++;
 
    // Initializam smenul lui Mars
    smen[comenzi[i]][i]++;
  }
   
  for(int i = 0; i < k; ++i)
    fin >> cost[i] >> profit[i] >> rezist[i];
 
  // Calculam smenul lui Mars
  for (int i = 0; i < k; ++i)
    for (int j = 1; j < n; ++j)
      smen[i][j] += smen[i][j - 1];
   
  int start = 1;
  if(n * k > 200000)
    start = 100;
 
  // Iteram prin toate t-urile
  for (int t = start; t <= n; ++t) {
    // Profitul scos pentru un t fixat
    long long profitt = 0LL;
    for (int i = 0; i < k; ++i) {
      int top = 0;
      for (int j = 0; j < n; j += t) // Pana aici e O(N*K*logN)
        bucks[top++] = getSmen(i, min(j + rezist[i] - 1, j + t - 1), n) - getSmen(i, j - 1, n);
 
      // Cel mai mare profit respectiv x-ul pt care se obtine profitul maximal
      long long bestprofitx = 0LL;
      int bestx = 0;
 
      // Suma alimentelor din bucketurile care au marime mai mica decat un x fixat
      int maimici = 0;
       
      // Vrem sa testam si X == 0
      bucks[top] = 0;
 
      sort(bucks, bucks + top + 1);
      for(int j = 0; j <= top; ++j) {
        long long profitx = 0LL;
        // Calculam profitul optim pentru un anumit punct
        profitx = (long long)maimici * profit[i] + (long long)bucks[j] * (top - j + 1) * profit[i] 
                - (long long)cost[i] * bucks[j] * top;
         
        // Actualizam optimul
        if (profitx > bestprofitx) {
          bestprofitx = profitx;
          bestx = bucks[j];
        }
         
        // Avem grija de elementele care vor fi mai mici decat urmatorul X
        maimici += bucks[j];
      }
 
      xint[i] = bestx;
      profitt += bestprofitx;
    }
     
    // Daca obtinem o solutie mai buna o actualizam
    if(profitt > best) {
      best = profitt;
      trez = t;
      for(int i = 0; i < k; ++i)
        xrez[i] = xint[i];
    }
  }
   
  //Afisam rezultatele
  fprintf(fout, "%lld\n%d\n", best, trez);
  for(int i = 0; i < k; ++i)
    fprintf(fout, "%d ", xrez[i]);
   
  // Inchidem fisierele
  fclose(fout);
  return 0;
}