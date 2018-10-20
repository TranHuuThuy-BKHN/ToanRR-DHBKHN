#include<iostream>
#include<vector>

using namespace std ;

struct Top {
	string word;
	bool visited;
	int ccnum, pre, post;
	int pos; //chi so cua dinh 
	int dist;
	int par;
	vector<int> near; //danh sach chi so cac dinh ke 
};

typedef Top* top;
typedef vector<top> Graph; //mot do thi thi chua danh sach cac dinh

//===========================Thuat toan DFS=============================================
void previsit(top &v, int &clock, int &cc) {
	v->ccnum = cc;
	v->pre = clock;
	clock += 1;
}

void postvisit(top &v, int &clock) {
	v->post = clock;
	clock += 1;
}

void explore(Graph &G, top &v, int &clock, int &cc) {
	v->visited = true;
	previsit(v, clock, cc);
	for(int i = 0 ; i < v->near.size() ; i++) {
		int index = v->near[i];
		if(G[index]->visited == false)
			explore(G, G[index], clock, cc);
	}
	postvisit(v, clock);		
}

void dfs(Graph &G) {
	int cc = 0, clock = 1;
	for(int i =  0 ; i < G.size() ; i++)
		G[i]->visited = false;
	for(int i = 0 ; i < G.size() ; i++)
		if(G[i]->visited == false) {
			cc += 1;
			explore(G, G[i], clock, cc);
		}
}
int main() {
	return 0;
}

