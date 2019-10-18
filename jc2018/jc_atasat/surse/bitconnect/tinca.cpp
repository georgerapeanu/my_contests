#include <bits/stdc++.h>
 
/*
 
Tinca
Solutie bitconnect
Complexitate: Nlog^2
 
*/
 
using namespace std;
 
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
} fin("bitconnect.in");
 
const int NBITS = 62;
 
int matr[NBITS][NBITS];
int dist[NBITS];
 
int coada[NBITS], st, dr;
bool query[NBITS];
 
int bfs(long long x, long long y) {
  if(x == y)
    return 0;
   
  for(int i = 0; i < NBITS; ++i)
    if((1LL << i) & y)
      query[i] = true;
    else
      query[i] = false;
 
  st = dr = 0;
 
  for(int i = 0; i < NBITS; ++i)
    if((1LL << i) & x) {
      coada[dr++] = i;
      dist[i] = 1;
      if(query[i])
        return 1;
    } else
      dist[i] = 100000;
   
  while(st < dr) {
    int nod = coada[st++];
    for(int i = 0; i < NBITS; ++i)
      if(matr[nod][i] > 0 && dist[nod] + 1 < dist[i]) {
        dist[i] = dist[nod] + 1;
        coada[dr++] = i;
        if(query[i])
          return dist[i];
      }
  }
   
  return -1;
}
 
int bitlist[NBITS], top;
 
int main() {
  int q, t;
  long long x, y;
  FILE *fout = fopen("bitconnect.out", "w");
   
  fprintf(fout, "bit\n");
   
  fin >> q;
  for(int i = 0; i < q; ++i) {
    fin >> t;
    if(t == 1) {
      top = 0;
      fin >> x;
      for(int i = 0; i < NBITS; ++i)
        if((1LL << i) & x)
          bitlist[top++] = i;
 
      for(int i = 0; i < top; ++i)
        for(int j = 0; j < top; ++j)
          matr[bitlist[i]][bitlist[j]]++;
    } else if(t == 2) {
      fin >> x;
      top = 0;
      for(int i = 0; i < NBITS; ++i)
        if((1LL << i) & x)
          bitlist[top++] = i;
 
      for(int i = 0; i < top; ++i)
        for(int j = 0; j < top; ++j)
          matr[bitlist[i]][bitlist[j]]--;
    } else {
      fin >> x >> y;
      fprintf(fout, "%d\n", bfs(x, y));
    }
  }
 
  fclose(fout);
  return 0;
}