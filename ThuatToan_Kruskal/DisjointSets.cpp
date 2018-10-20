#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

struct Top {
	int pos, par, rank;
};

struct Edge {
	int start, end, dist;	
};

typedef vector<Edge> edge;
typedef vector<Top*> top;
//khai bao tap cac canh, va tap cac dinh cua do thi cua do thi 
static edge E; 
static top V;
//ham khoi tao mot tap chi chua mot dinh x
void markset(Top* &x) {
	x->par = x->pos;
	x->rank = 0;
}

//ham tim ra not cha cua node x dong thoi sua doi cha cua tat ca cac dinh tren duong di cua x, lam giam do cao cua cay
int find(Top* &x) {
	if(x->pos != x->par)
		x->par = find(V[x->par]);
	return x->par;	
}
//ham hop hai tap chu nut x va nut y
void unions(Top* &x, Top* &y) {
	int parX = find(x), parY = find(y);
	if(parX == parY) return;
	else if(V[parX]->rank > V[parY]->rank)
		V[parY]->par = V[parX]->pos;
	else {
		V[parX]->par = V[parY]->pos;
		//neu hai cay co cung do cao thi khi do viec hop hai cay se lam cay moi co do cao tang len 1
		if(V[parX]->rank == V[parY]->rank)
			V[parY]->rank = V[parX]->rank + 1;
	}	
}

bool cmp_dist(const Edge &e1, const Edge &e2) {
	return e1.dist < e2.dist;	
}

void kruskal(int &weight, edge &X) {
	weight = 0;
	for(int i = 0; i < V.size(); i++)
		markset(V[i]);
	//sap xep cac canh cua do thi theo thu tu tang dan
	sort(E.begin(), E.end(), cmp_dist);
	for(int i = 0; i < E.size(); i++) {
		int u = E[i].start, v = E[i].end;
		if(find(V[u]) != find(V[v])) {
			weight += E[i].dist;
			X.push_back(E[i]);
			unions(V[u], V[v]);
		}
	}
}

Top* init(int pos) {
	Top* p =  new Top;
	p->pos = pos;
	return p;	
}

void readFile(ifstream &ifs) {
	ifs.open("data.txt");
	int size = 0;
	ifs >> size;
	for(int i = 0; i < size; i++){
		Top *p = init(i);
		V.push_back(p);
	}
	while(ifs.eof() == false) {
		Edge e;
		ifs >> e.start >> e.end >> e.dist;
		E.push_back(e);
	}
	ifs.close();	
}

int main(){
	int weight;
	edge X;
	ifstream ifs;
	readFile(ifs);
	kruskal(weight, X);
	cout << weight << endl;
	for(int i = 0; i < X.size(); i++) {
		cout << X[i].start << " " << X[i].end << " " << X[i].dist << endl;
	}
	return 0 ;
}
