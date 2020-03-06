#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<algorithm>
#define NIL -1
#define NAN -1

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

top init(string word, int pos) {
	top p = new Top;
	p->word = word; p->pos = pos; p->visited = false;
	p->dist = NAN; p->par = NIL;
	return p;	
}

//==========================BFS xac dinh duong di ngan nhat tu dinh rs den rd============================
void bfs(Graph &G, top &rs, top &rd) {
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
	//ta can in ra so tu la khoang cach cua rd toi rs luc nay
	if(rd->par == NIL){
		cout << "Khong Ton Tai Duong Di";
		return;
	}
	top temp = G[rd->par];
	cout << rd->word;
	for(int i = 0 ; i < rd->dist ; i++) {
		cout << "<--" << temp->word ;
		temp = G[temp->par];
	}
	for(int i = 0 ; i < G.size() ; i++){
		G[i]->dist = NAN;
		G[i]->par = NIL;
	}
}
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
//============================================================================
//ham tra ve do thi nguoc cua do thi G
Graph G_R(Graph G) {
	Graph GR;
	for(int i = 0 ; i < G.size() ; i++) {
		top p = init(G[i]->word, G[i]->pos);
		GR.push_back(p);
	}
	//chinh lai huong cua canh
	for(int i = 0 ; i < G.size() ; i++) {
		for(int j = 0 ; j < G[i]->near.size() ; j++) {
			int index1 = G[i]->near[j], index2 = G[i]->pos;
			GR[index1]->near.push_back(index2);
		}
	}
	return GR;	
}

bool cmp_post(const top &a, const top &b) {
	return a->post > b->post;
}
//ham tra ve so thanh phan lien thong manh, va chay dfs tren do thi G
int getLTM(Graph &G) {
	Graph GR = G_R(G);
	dfs(GR);
	//sap xep cac dinh trong do thi nguoc voi so post giam dan
	sort(GR.begin(), GR.end(), cmp_post);
	int count = 0, clock = 1, cc = 0;
	while(count < GR.size()) {
		int index = GR[count]->pos;
		if(G[index]->visited == false) {
			cc += 1;
			explore(G, G[index], clock, cc);
		}
		count++;
	}
	return cc;
}
//ham in ra cac tu cung nam trong thanh phan lien thong manh, ham nay can thuc hien sau ham getLTM(G)
void printWord(Graph G, top V) {
	for(int i = 0 ; i < G.size() ; i++)
		if(G[i]->ccnum == V->ccnum && G[i]->word.compare(V->word) != 0)
			cout << G[i]->word << "\t";
}

bool check(char ch, string word) {
	for(int i = 0 ; i < 5; i++) {
		if(ch == word[i])
			return true;
	}
	return false;	
}

bool check(string word1, string word2) {
	for(int i = 1 ; i < 5 ; i++) {
		if(check(word1[i], word2) == false)
			return false;
	}
	return true;
}

void menu(Graph G, int ltm) {
	int LuaChon;
	do{
		cout << "\n==============MENU==============\n";
		cout << "\n0.Thoat";
		cout << "\n1.So Thanh Phan Lien Thong Manh";
		cout << "\n2.Cac Tu Trong Cung Thanh Phan Lien Thong Manh";
		cout << "\n3.Duong Di Ngan Nhat Giua Hai Tu\n";
		cout << "\n==============END===============\n";
		do{
			cout << "\nLua Chon : "; cin >> LuaChon;
		}while(LuaChon < 0 || LuaChon > 3);
		if(LuaChon) {
			if(LuaChon == 1)
				cout << "So Thanh Phan Lien Thong Manh : " << ltm;
			if(LuaChon == 2) {
				string word;
				cout << "\nNhap word : "; fflush(stdin); getline(cin, word);
				top V = NULL;
				for(int i = 0 ; i < G.size() ; i++)
					if(G[i]->word.compare(word) == 0)
						V = G[i];
				if(V == NULL)
					cout << "\nTu Do Khong Co Trong Do Thi\n";
				else printWord(G, V);			
			}	
			if(LuaChon == 3) {
				string word1, word2;
				cout << "Word Bat Dau : "; fflush(stdin); getline(cin, word1);
				cout << "Word Ket Thuc : "; fflush(stdin); getline(cin, word2);
				top rs = NULL, rd = NULL;
				for(int i = 0 ; i < G.size() ; i++) {
					if(G[i]->word.compare(word1) == 0)
						rs = G[i];
					else if(G[i]->word.compare(word2) == 0)
						rd = G[i];
				}
				if(rd != NULL && rs != NULL) {
					printRoad(G, rs, rd);
				}
				else cout << "\nMot Trong Cac Tu Khong Co Trong Do Thi\n";
			}
			cout << endl;	
			system("pause"); system("cls");
		}
	}while(LuaChon);
}

int main() {
	Graph G;
	ifstream ifs;
	ifs.open("sgb-words.txt");
	string word;
	int pos = 0, ltm;
	while(ifs.eof() == false) {
		fflush(stdin);
		getline(ifs, word);
		top p = init(word, pos++);
		G.push_back(p);
	}
	for(int i = 0 ; i < G.size() ; i++) {
		for(int j = 0 ; j < G.size() ; j++) {
			if(j != i && check(G[i]->word, G[j]->word)) {
				G[i]->near.push_back(G[j]->pos);
			}
		}
	}
	ltm = getLTM(G);
	menu(G, ltm);
	return 0;
}
