#include<bits/stdc++.h>
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>

using namespace std;

void killProcessByName(const char *filename){
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}


const int NMAX = 106000;
const int targetN = 450;
const int LGMAX = 62;
const int LEN = 1e4;
const int Used_Nodes_st = 1;
const int Used_Nodes_dr = 5;
const int Random_Nodes = 2;
const int Random_Querys = 4;
const double TIME_LIMIT = 1.5;
const int TEST_CLOCK_DURATION = TIME_LIMIT * CLOCKS_PER_SEC;



namespace N2logN{
	FILE *f = fopen("bitconnect.in","r");
	FILE *g1 = fopen("bitconnect_bitMode.out","w");
	FILE *g2 = fopen("bitconnect_connectMode.out","w");
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

}

namespace N2{
	FILE *f = fopen("bitconnect.in","r");
	FILE *g1 = fopen("bitconnect_bitMode.out","w");
	FILE *g2 = fopen("bitconnect_connectMode.out","w");
	char buff[LEN];
	int N;
	int ind = LEN - 1;
	unordered_map<long long,int> viz;
	unordered_map<long long,int> Nodes;
	unordered_map<long long,unordered_set<long long> > G;

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

}

namespace Nlog3N{
	FILE *f = fopen("bitconnect.in","r");
	FILE *g1 = fopen("bitconnect_bitMode.out","w");
	FILE *g2 = fopen("bitconnect_connectMode.out","w");
	char buff[LEN];
	int ind = LEN - 1;

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

	int N;

	int viz[LGMAX + 5];
	long long Q[LGMAX + 5];
	int stq,drq;

	set<long long> S[LGMAX * LGMAX + 5];

	void baga(long long val){
		for(int bit = 0;bit < LGMAX;bit++){
			if(!((val >> bit) & 1)){
				continue;
			}
			for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
				if(!((val >> next_bit) & 1)){
					continue;
				}
				S[bit * LGMAX + next_bit].insert(val);
			}
		}
	}

	void scoate(long long val){
		for(int bit = 0;bit < LGMAX;bit++){
			if(!((val >> bit) & 1)){
				continue;
			}
			for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
				if(!((val >> next_bit) & 1)){
					continue;
				}
				S[bit * LGMAX + next_bit].erase(val);
			}
		}
	}

	bool exists(int first_bit,int second_bit){
		if(first_bit > second_bit){
			swap(first_bit,second_bit);
		}
		return !S[first_bit * LGMAX + second_bit].empty();
	}

	int BFS(long long x,long long y){

		if(x == y){
			return 0;
		}

		stq = 1;drq = 0;
		memset(viz,0,sizeof(viz));

		for(int bit = 0;bit < LGMAX;bit++){
			if((x >> bit) & 1){
				viz[bit] = 1;
				Q[++drq] = bit;
				if((y >> bit) & 1){
					return 1;
				}
			}
		}

		while(stq <= drq){
			int bit = Q[stq++];
			for(int next_bit = 0;next_bit < LGMAX;next_bit++){
				if(!viz[next_bit] && exists(bit,next_bit)){
					viz[next_bit] = 1 + viz[bit];
					Q[++drq] = next_bit;
					if((y >> next_bit) & 1){
						return viz[next_bit];
					}
				}
			}
		}
		return -1;
	}

}

namespace Nlog2N{
	FILE *f = fopen("bitconnect.in","r");
	FILE *g1 = fopen("bitconnect_bitMode.out","w");
	FILE *g2 = fopen("bitconnect_connectMode.out","w");
	char buff[LEN];
	int ind = LEN - 1;

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

	int N;

	int viz[LGMAX + 5];
	long long Q[LGMAX + 5];
	int stq,drq;

	int how_many[LGMAX * LGMAX + 5];

	void baga(long long val){
		for(int bit = 0;bit < LGMAX;bit++){
			if(!((val >> bit) & 1)){
				continue;
			}
			for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
				if(!((val >> next_bit) & 1)){
					continue;
				}
				how_many[bit * LGMAX + next_bit]++;
			}
		}
	}

	void scoate(long long val){
		for(int bit = 0;bit < LGMAX;bit++){
			if(!((val >> bit) & 1)){
				continue;
			}
			for(int next_bit = bit + 1;next_bit < LGMAX;next_bit++){
				if(!((val >> next_bit) & 1)){
					continue;
				}
				how_many[bit * LGMAX + next_bit]--;
			}
		}
	}

	bool exists(int first_bit,int second_bit){
		if(first_bit > second_bit){
			swap(first_bit,second_bit);
		}
		return how_many[first_bit * LGMAX + second_bit] > 0;
	}

	int BFS(long long x,long long y){

		if(x == y){
			return 0;
		}

		stq = 1;drq = 0;
		memset(viz,0,sizeof(viz));

		for(int bit = 0;bit < LGMAX;bit++){
			if((x >> bit) & 1){
				viz[bit] = 1;
				Q[++drq] = bit;
				if((y >> bit) & 1){
					return 1;
				}
			}
		}

		while(stq <= drq){
			int bit = Q[stq++];
			for(int next_bit = 0;next_bit < LGMAX;next_bit++){
				if(!viz[next_bit] && exists(bit,next_bit)){
					viz[next_bit] = 1 + viz[bit];
					Q[++drq] = next_bit;
					if((y >> next_bit) & 1){
						return viz[next_bit];
					}
				}
			}
		}
		return -1;
	}

}

struct Tree{
	int Used_Nodes;///de la [Used_Nodes in colo sunt biti care intra in clici la alte noduri
	vector<int> fathers;///fathers de la [Used_Nodes devine nodul cu care se pune in clica
	vector<int> nodes;
	vector< long long > node_clique_mask;
	void init(){
		nodes.resize(LGMAX);
		fathers.resize(LGMAX);
		node_clique_mask.resize(LGMAX);
		for(auto &it:nodes){
			it = -1;
		}
		for(auto &it:fathers){
			it = -1;
		}
		for(int i = 0;i < LGMAX;i++){
			node_clique_mask[i] = 1LL << i;
		}
	}

	void afis(){
		for(int i = 0;i < Used_Nodes;i++){
			cout << nodes[i] << " " << fathers[nodes[i]] << "\n";
		}
		cout << "\n\n\n";
	}
};

Tree Generate_Bit_Trees(int Used_Nodes,int wanted_diameter){///vom genera 2 arbori independeti pe biti pt a permite raspunsuri de -1
	vector<int> nodes;
	for(int i = 0;i < LGMAX;i++){
		nodes.push_back(i);
	}
	random_shuffle(nodes.begin(),nodes.end());
	Tree ans;ans.init();
	ans.nodes = nodes;
	ans.Used_Nodes = Used_Nodes;
	int split_trees = (wanted_diameter - 1) + rand() % (Used_Nodes - wanted_diameter + 1);//first tree:0...split_tree
	for(int i = 1;i < wanted_diameter;i++){
		ans.fathers[nodes[i]] = nodes[i - 1];
	}

	for(int i = wanted_diameter;i <= split_trees;i++){
		ans.fathers[nodes[i]] = nodes[rand() % i];
	}

	for(int i = split_trees + 2;i < Used_Nodes;i++){
		ans.fathers[nodes[i]] = nodes[split_trees + 1 + (rand() % (i - split_trees - 1))];
	}

	for(int i = Used_Nodes;i < (int)nodes.size();i++){
		int cli = rand() % Used_Nodes;
		ans.fathers[nodes[i]] = nodes[cli];
		ans.node_clique_mask[nodes[cli]] |= (1LL << nodes[i]);
	}

	return ans;
}

set<long long> Active_Nodes_By_Now;

vector<vector<long long> > INPUT;

void test_push_insert(long long x){
	INPUT.push_back({1,x});
}
void test_push_erase(long long x){
	INPUT.push_back({2,x});
}
void test_push_query(long long x,long long y){
	INPUT.push_back({3,x,y});
}

long long get_random_from_set(){
	int pos = rand() % Active_Nodes_By_Now.size();
	for(auto it:Active_Nodes_By_Now){
		if(!pos){
			return it;
		}
		pos--;
	}
	return *Active_Nodes_By_Now.begin();
}


void tranzition_between_Set_and_Tree(Tree a){
	bool exists_edge[LGMAX][LGMAX];
	memset(exists_edge,0,sizeof(exists_edge));
	vector<long long> toErase;
	for(auto it:Active_Nodes_By_Now){
		bool ok = 1;
		for(int i = 0;i < LGMAX;i++){
			for(int j = i + 1;j < LGMAX;j++){
				if(((it >> i) & 1) && ((it >> j) & 1)){
					if(a.fathers[i] == j || a.fathers[j] == i){
						continue;
					}
					ok = 0;
				}
			}
		}
		if(ok){
			for(int i = 0;i < LGMAX;i++){
				for(int j = i + 1;j < LGMAX;j++){
					if(((it >> i) & 1) && ((it >> j) & 1)){
						if(a.fathers[i] == j || a.fathers[j] == i){
							exists_edge[i][j] = 1;
							exists_edge[j][i] = 1;
						}
					}
				}
			}
		}
		else{
			toErase.push_back(it);
		}
	}

	for(auto it:toErase){
		assert(Active_Nodes_By_Now.count(it) != 0);
		Active_Nodes_By_Now.erase(it);
		test_push_erase(it);
	}

	for(int i = 0;i < a.Used_Nodes;i++){
		if(a.fathers[a.nodes[i]] == -1 || exists_edge[a.fathers[a.nodes[i]]][a.nodes[i]]){
			continue;
		}
		assert(Active_Nodes_By_Now.count((1LL << a.nodes[i]) | (1LL << a.fathers[a.nodes[i]])) == 0);
		Active_Nodes_By_Now.insert((1LL << a.nodes[i]) | (1LL << a.fathers[a.nodes[i]]));
		test_push_insert((1LL << a.nodes[i]) | (1LL << a.fathers[a.nodes[i]]));
	}

	for(int i = 0;i < a.Used_Nodes;i++){
		if(!Active_Nodes_By_Now.count(a.node_clique_mask[a.nodes[i]])){
			assert(Active_Nodes_By_Now.count(a.node_clique_mask[a.nodes[i]]) == 0);
			test_push_insert(a.node_clique_mask[a.nodes[i]]);
			Active_Nodes_By_Now.insert(a.node_clique_mask[a.nodes[i]]);
		}
	}

}

void transform_set_base_on_Tree(Tree a,int how_many_bonus_nodes){
	tranzition_between_Set_and_Tree(a);
	for(int i = 0;i < a.Used_Nodes && how_many_bonus_nodes;i++){
		for(long long mask = a.node_clique_mask[a.nodes[i]] & (a.node_clique_mask[a.nodes[i]] - 1);mask && how_many_bonus_nodes;mask = (mask - 1) & a.node_clique_mask[a.nodes[i]]){
			if(!Active_Nodes_By_Now.count(mask)){
				how_many_bonus_nodes--;
				assert(Active_Nodes_By_Now.count(mask) == 0);
				Active_Nodes_By_Now.insert(mask);
				test_push_insert(mask);
			}
		}
	}
}

void ask_querys(Tree a,int how_many_random){
	vector< pair<long long,long long> > query;
	for(int i = 0;i < a.Used_Nodes;i++){
		for(int j = i;j < a.Used_Nodes;j++){
			query.push_back({a.node_clique_mask[a.nodes[i]],a.node_clique_mask[a.nodes[j]]});
		}
	}

	while(Active_Nodes_By_Now.size() && how_many_random--){
		long long x,y;
		x = get_random_from_set();
		y = get_random_from_set();
		query.push_back({x,y});
	}

	random_shuffle(query.begin(),query.end());

	for(auto it:query){
		test_push_query(it.first,it.second);
	}

}

void generate_input(int targetN){
	INPUT.clear();
	FILE *g = fopen("bitconnect.in","w");
	Active_Nodes_By_Now.clear();
	while(targetN > (int)INPUT.size()){
		Tree a;

		int used_bits = (rand() % (Used_Nodes_dr - Used_Nodes_st + 1) ) + Used_Nodes_st;

		a = Generate_Bit_Trees(used_bits,rand() % used_bits + 1);

		transform_set_base_on_Tree(a,rand() % Random_Nodes);
		ask_querys(a,rand() % Random_Querys);
	}

	fprintf(g,"%d\n",INPUT.size());
	for(auto it:INPUT){
		for(auto it2:it){
			fprintf(g,"%lld ",it2);
		}
		fprintf(g,"\n");
	}

	fclose(g);
}

string toString(int val){
    string ans;
    do
    {
        ans += (val % 10) + '0';
        val /= 10;
    }
    while(val);
	reverse(ans.begin(),ans.end());
    return ans;
}

void afis(vector< vector<long long> > INPUT,int test){
    ofstream g("grader_test" + toString(test) + ".in");
	g << INPUT.size() << "\n";
	for(auto it:INPUT){
		for(auto it2:it){
			g << it2 << " ";
		}
		g << "\n";
	}

	g.close();
}

int main(){
	srand(time(NULL));

	 for(int test = 2;test <= 2;test++){
		vector< vector<long long> > BEST_INPUT;
		long long best_dif = -1;
		for(int epoch = 1;epoch <= 20;epoch++){
			generate_input(targetN);
			cout << "done epoch " << epoch << "\n";
			long long _start = clock();
			system("Nlog2N.exe");
			long long _end = clock();
			long long duration = _end - _start;

			if(duration > best_dif){
				best_dif = duration;
				BEST_INPUT = INPUT;
			}
		}
		afis(BEST_INPUT,test);
		cout << "DONE TEST " << test << "\n";
	}
	
	return 0;
}
