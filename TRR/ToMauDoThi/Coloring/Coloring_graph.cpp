#include<iostream>
#include<Vector>
#include<fstream>
#include<algorithm>

using namespace std;

string Color[7] = {"black", "red", "green", "yellow", "pink", "blue", "orange"};

struct Dinh{
	int Pos, NumOfColor;
	vector<Dinh*> NeiBor; //Danh sach cac hang xom
	bool Ok ;//danh dau la dinh da duoc to mau hay chua
};

struct Canh {
	int s, e;
};
//=========================THUAT TOAN TO MAU THAM LAM================================
bool OkColor(int j, vector<Dinh*> N){ //ham kiem tra mau j khac voi tat ca cac mau cua cac dinh ke da duoc to mau
	for(int i = 0 ; i < N.size() ; i++)
		if(j == N[i]->NumOfColor && N[i]->Ok) return false;
	return true;	
}

void Greedy(Dinh* &P, int n) {//Ham Xac Dinh Mau Dinh Ve_i
	if(P->NeiBor.size() == 0) P->NumOfColor = 1; //Neu Khong Co Hang Xom Thi Mau Bang 1
	else{
		for(int j = 1 ; j <= n ; j++){
			if(OkColor(j, P->NeiBor)){//Ta Lay Mau Be Nhat Va Khac Mau Tat Ca Cac Hang Xom
				P->NumOfColor = j;
				break;
			} 
		}
	}
	P->Ok = true;
}

void GreedyAlgorithm(Dinh* *P, int n){
	for(int i = 0 ; i < n ; i++){// Ban Dau Cho Tat Ca Cac Dinh Cung Mot Mau, va P[i]->Ok = false
		P[i]->Ok = false;
		P[i]->NumOfColor = 1;
	}
	for (int i = 0 ; i < n; i++)
		Greedy(P[i], n);
}
//======================KET THUC TO MAU THAM LAM====================================
void AddDinh(Canh c, Dinh* *P){
	int s = c.s, e = c.e ;
	P[s - 1]->NeiBor.push_back(P[e - 1]) ;//cho vao danh sach hang xom
	P[e - 1]->NeiBor.push_back(P[s - 1]) ;
}
//Ham Tao Tat Ca Cac Dinh Va Luu Danh Sach Cac Dinh Ke Voi No
void AddAllDinh(Canh *C, Dinh* *P, int m){
	for(int i = 0 ; i < m ; i++)
		AddDinh(C[i], P);	
}

bool Cmp_Deg(const Dinh* P1, const Dinh* P2){
	return P1->NeiBor.size() > P2->NeiBor.size();
}

void OutPut(Dinh* *P, int n, Canh *C, int m, ofstream &ofs){
	ofs << "graph dothi\n{\n" ;
	for(int i = 0 ; i < n ; i++){
		ofs << P[i]->Pos << "[fillcolor = " << Color[P[i]->NumOfColor] << ", style = filled];\n";
	}
	for(int i = 0 ; i < m ; i++)
		ofs << C[i].s << " -- " << C[i].e << ";" << endl;
	ofs << "}";
}

int main() {
	int n, m ;
	ifstream ifs ;
	ifs.open("dothi.txt") ;
	if(ifs.fail()){
		cout << "Loi Mo File\nThay Chua Co File dothi.txt\n^^Du Lieu Tren Trang bkict.org Bi Loi^^";
		return 0;
	}
	ifs >> n >> m;
	Canh *C = new Canh[m];
	Dinh* *P = new Dinh* [n];
	for(int i = 0; i < n ; i++){
		P[i] = new Dinh; P[i]->Pos = i + 1 ;//Duyet Tham Lam Theo Thu Tu Mac Dinh 
	}
	for(int i = 0 ; i < m ; i++)
		ifs >> C[i].s >> C[i].e ;
	ifs.close();
	AddAllDinh(C, P, m);//tao lap cac dinh
	sort(P, P + n , Cmp_Deg ); //sap xep cac dinh them bac 
	GreedyAlgorithm(P, n);
	ofstream ofs;
    ofs.open("dothitomau.txt");
	OutPut(P, n, C, m, ofs);
	ofs.close();
	return 0;
}
