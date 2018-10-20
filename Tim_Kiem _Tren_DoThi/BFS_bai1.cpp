#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#define NIL -1
#define NAN -1
#define CHECK 1

using namespace std ;
//thuat toan BFS don gian voi do dai moi canh la 1, in ra mot duong di ngan nhat trong do thi

struct Top {
	string word;
	int pos; //vi tri cua dinh
	int dist;
	int par; //chi so cua dinh truoc no
	vector<int> near; //chi so cac dinh ke	
};

typedef Top* top;
typedef vector<top> Graph;
//ham khoi tao mot dinh
top init(string word, int pos) {
	top p = new Top;
	p->word = word; p->pos = pos;
	return p;	
}
//==========================BFS xac dinh duong di ngan nhat tu dinh rs den rd============================
void bfs(Graph &G, top &rs, top &rd) {
	for(int i = 0 ; i < G.size() ; i++) {
		G[i]->par = NIL;
		G[i]->dist = NAN;
	}
	queue<top> Q;//khoi tao hang doi
	rs->dist = 0;
	Q.push(rs);
	while(Q.empty() == false) {
		top u = Q.front();
		Q.pop(); //loai bo dau hang doi
		for(int i = 0 ; i < u->near.size() ; i++) {
			int index = u->near[i];
			if(G[index]->dist == NAN) {
				G[index]->dist = u->dist + 1;
				G[index]->par = u->pos; 				//luu lai dinh truoc no trong duong di
				Q.push(G[index]); 						//cho vao cuoi hang doi
				//neu da di den dich thi dung lai
				if(G[index]->word.compare(rd->word) == 0)
					return;
			}
		}
	}
}
//ham in ra duong di
void printRoad(Graph &G, top &rs, top &rd) {
	bfs(G, rs, rd);
	if(rd->par == NIL)
		cout << "Khong Ton Tai Tu " << rd->word << " Trong Do Thi" << endl;
	else {
		//ta can in ra so tu la khoang cach cua rd toi rs luc nay
		top temp = G[rd->par];
		cout << rd->word;
		for(int i = 0 ; i < rd->dist ; i++) {
			cout << "<--" << temp->word ;
			temp = G[temp->par];
		}
	}		
}

bool check(string word1, string word2) {
	int count = 0;
	for(int i = 0 ; i < 5 ; i++) {
		if(word1[i] != word2[i])
			count++;
	}
	if(count == 1)
		return true;
	return false;	
}

int main(){
	Graph G;
	ifstream ifs;
	ifs.open("sgb-words.txt");
	string word;
	int pos = 0;
	while(ifs.eof() == false) {
		getline(ifs, word);
		top p = init(word, pos++);
		G.push_back(p);
	}
	//thuc hien them dinh ke
	for(int i = 0 ; i < G.size() - 1 ; i++) {
		for(int j = i + 1 ; j < G.size() ; j++) {
			if(check(G[i]->word, G[j]->word)){
				G[i]->near.push_back(G[j]->pos);
				G[j]->near.push_back(G[i]->pos);
			}
		}
	}
	string word1, word2;
	cout << "Nhap Tu Bat Dau : "; fflush(stdin);
	getline(cin ,word1);
	cout << "Nhap Tu Ket Thuc : "; fflush(stdin);
	getline(cin ,word2);
	int rs, rd;
	for(int i = 0 ; i < G.size() ; i++){
		if(G[i]->word.compare(word1) == 0)
			rs = i;
		if(G[i]->word.compare(word2) == 0)
			rd = i;	
	}
	printRoad(G, G[rs], G[rd]);
	return 0 ;
}
