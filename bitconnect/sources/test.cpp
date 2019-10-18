#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
 
using namespace std;
 
ifstream cin ("bitconnect.in");
ofstream cout ("bitconnect.out");
 
const int INF = 1e9;
 
int n;
int type, x, y;
 
map <long long, bool> f;
set <long long> v;
 
int bfs(int st, int dr) {
  queue <int> q;
  map <long long, int> dist;
  for(auto it : v)
    dist[it] = INF;
  q.push(st);
  dist[st] = 0;
  while(!q.empty()) {
    int nod = q.front();
    q.pop();
    if(!f[nod])
      continue;
    for(auto it : v) {
      if(f[it] && (nod & it) && dist[it] > dist[nod] + 1) {
        dist[it] = dist[nod] + 1;
        q.push(it);
      }
    }
  }
  if(dist[dr] != INF)
     return dist[dr];
  return -1;
}
 
int main() {
  cin >> n;
  cout << "bit\n";
  for(int i = 1; i <= n; i++) {
    cin >> type;
    if(type == 1) {
      cin >> x;
      f[x] = 1;
      v.insert(x);
    } else if(type == 2) {
      cin >> x;
      f[x] = 0;
      v.erase(x);
    } else {
      cin >> x >> y;
      cout << bfs(x, y) << "\n";
    }
  }
  return 0;
}