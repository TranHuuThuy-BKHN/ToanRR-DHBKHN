#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<algorithm>
#define NIL -1
#define NAN -1
#define CHECK 1

using namespace std;

struct Top {
	string word;
	bool visited;
	int ccnum, pre, post;
	int pos; //chi so cua dinh, phuc vu viec them cac dinh ke
	int dist; //BFS
	int par; //chi so cua dinh truoc no, de su dung BFS
	vector<int> near;
};

typedef Top* top;
typedef vector<top> Graph;

top init(string word, int pos) {
	top p = new Top;
	p->word = word; 
	p->pos = pos; 
	p->dist = NAN;
	p->par = NIL;
	return p;
}

//=================================DFS==================================
void previsit(top &v, int &clock, int cc) {
	v->ccnum = cc;
	v->pre = clock;
	clock = clock + 1;	
}

void postvisit(top &v, int &clock) {
	v->post = clock;
	clock = clock + 1;
}

void explore(Graph &G, top &v, int &clock, int &cc) {
	v->visited = true;
	previsit(v, clock, cc);
	for(int i = 0 ; i < v->near.size() ; i++) {
		int index = v->near[i];
		if(G[index]->visited == false)
			explore(G, G[index], clock , cc);
	}
	postvisit(v, clock);
}

static int LT = 0;
void dfs(Graph &G) {
	int cc = 0, clock = 1;
	for(int i = 0 ; i < G.size() ; i++)
		G[i]->visited = false;
	for(int i = 0 ; i < G.size() ; i++)
		if(G[i]->visited == false) {
			cc = cc + 1;
			explore(G, G[i], clock, cc);
		}
	LT = cc;			
}
//========================KET THUC DFS==================================================

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

//ham tra ve so thanh phan lien thong manh, chay dfs tren do thi G
int getLTM(Graph &G) {
	Graph GR = G_R(G);
	dfs(GR);
	//sap xep cac dinh trong do thi nguoc voi so post giam dan
	sort(GR.begin(), GR.end(), cmp_post);
	int count = 0, clock = 1, cc = 0;
	for(int i = 0 ; i < G.size() ; i++)
			G[i]->visited = false;
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

//==========================BFS xac dinh duong di ngan nhat tu dinh rs den rd============================
//do khoang cach gia hai tu chi la 1 nen ta khong can thiet cai dat hang doi uu tien
void bfs(Graph &G, top &rs, top &rd) {
	for(int i = 0 ; i < G.size() ; i++){
		G[i]->dist = NAN;
		G[i]->par = NIL;
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

//ham in ra duong di gia hai dinh
void printRoad(Graph &G, top &rs, top &rd) {
	bfs(G, rs, rd);
	//ta can in ra so tu la khoang cach cua rd toi rs luc nay
	if(rd->par == NIL){
		cout << "\nKhong Ton Tai Duong Di\n";
		return;
	}
	top temp = G[rd->par];
	cout << rd->word;
	for(int i = 0 ; i < rd->dist ; i++) {
		cout << "<--" << temp->word ;
		temp = G[temp->par];
	}
}

//ham in ra duong di giua hai tu
void printRoad(Graph &G, string word1, string word2) {
	top rs = NULL, rd = NULL;
	for(int i = 0 ; i < G.size() ; i++) {
		if(G[i]->word.compare(word1) == 0)
			rs = G[i];
		else if(G[i]->word.compare(word2) == 0)
			rd = G[i];
	}
	if(rs != NULL && rd != NULL)
		printRoad(G, rs, rd);
	else cout << "\nMot Trong Hai Tu Khong Co Trong Do Thi\n";	
}

bool check1(string word1, string word2) {
	int count = 0;
	for(int i = 0 ; i < 5 ; i++) {
		if(word1[i] != word2[i])
			count++;
	}
	if(count == 1)
		return true;
	return false;	
}

bool check2(string word1, string word2) {
	int ch[5] = {0}, d = 0;
	for(int i = 1 ; i < 5 ; i++) {
		for(int j = 0 ; j < 5 ; j++) {
			if(word1[i] == word2[j] && ch[j] != CHECK) {
				ch[j] = CHECK;
				d++;
				break;
			}
		}
	}
	if(d == 4) 
		return true;
	return false;	
	
}

void menu(Graph G1, Graph G2) {
	int LuaChon, ltm;
	string word1, word2, word;
	do{
		cout << "\n========================MENU========================\n";
		cout << "\n0.thoat";
		cout << "\n1.so thanh phan lien thong cua do thi VO huong";
		cout << "\n2.duong di trong do thi VO huong";
		cout << "\n3.duong di trong do thi CO huong";
		cout << "\n4.so thanh phan lien thong MANH";
		cout << "\n5.cac tu trong cung thanh phan lien thong MANH";
		cout << "\n=========================END========================\n";
		do{
			cout << "\nLuaChon : "; cin >>LuaChon;
		}while(LuaChon < 0 || LuaChon > 5);
		switch(LuaChon) {
			case 0: break;
			case 1: dfs(G1);
				cout << "So Thanh Phan Lien Thong Tren Do Thi Vo Huong " << LT << endl; break;		
			case 2:
			case 3:
					cout << "Nhap word1 : "; fflush(stdin); getline(cin, word1);
					cout << "Nhap word2 : "; fflush(stdin); getline(cin, word2);	
					if(LuaChon == 2) 
						printRoad(G1, word1, word2); 
					else printRoad(G2, word1, word2);
					break;				
			default:
					ltm = getLTM(G2);
					if(LuaChon == 4)
						cout << "So Thanh Phan Lien Thong Manh Cua Do Thi Co Huong " << ltm << endl;
					else {
						cout << "Nhap word : "; fflush(stdin); getline(cin ,word);
						top V = NULL;
						for(int i = 0 ; i < G2.size() ; i++)
							if(G2[i]->word.compare(word) == 0)
								V = G2[i];
						if(V == NULL)
							cout << "\nWord Khong Co Trong Tu Dien\n";
						else{
							cout << "\nCac Tu Trong Cung Thanh Phan Lien Thong Manh\n";
							printWord(G2, V);
						}				
					}	
		}
		if(LuaChon) {
			cout << endl;
			system("pause");
			system("cls");
		}
	}while(LuaChon);	  
}

int main() {
	Graph G1, G2; //khoi tao mot do thi vo huong va mot do thi co huong
	ifstream ifs;
	ifs.open("sgb-words.txt");
	if(ifs.fail()) {
		cout << "\nCan Co File 'sgb-words.txt' O Cung Thu Muc Voi File Source Code";
		return 0;
	}
	cout << "\nDang Tao Hai Do Thi, Qua Trinh Can Mot So Thoi Gian\n";
	string word;
	int pos = 0;
	while(ifs.eof() == false) {
		getline(ifs, word);
		top p1 = init(word, pos);
		top p2 = init(word, pos++);
		for(int i = 0 ; i < G1.size() ; i++)
			if(check1(G1[i]->word, p1->word)) {
				G1[i]->near.push_back(p1->pos);
				p1->near.push_back(G1[i]->pos);
			}
		G1.push_back(p1);
		for(int i = 0 ; i < G2.size() ; i++) {
			if(check2(G2[i]->word, p2->word)) {
				G2[i]->near.push_back(p2->pos);
			}
			if(check2(p2->word, G2[i]->word)) {
				p2->near.push_back(G2[i]->pos);
			}
		}
		G2.push_back(p2);
	}
	system("cls");
	menu(G1, G2);
	return 0;
}
