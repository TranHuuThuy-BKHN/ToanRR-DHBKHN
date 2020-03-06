#include<iostream>
#include<Vector>

using namespace std;

string Color[7] = {"black", "red", "green", "blue", "yellow", "orange", "pink"};

struct Dinh{
	int Pos, NumOfColor;//chi so va so mau cua dinh
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
//ham hiem tra do thi co chinh quy hay khong
bool ChinhQuy(Dinh* *P, int n){
	for(int i = 0 ; i < n - 1 ; i++)
		if(P[i]->NeiBor.size() != P[i+1]->NeiBor.size()) return false;
	return true;	
}

bool App(int d, int *a, int n){//Ham kiem tra so nguyen d da xuat hien trong mang a co n phan tu chua,xem dong 74
	for(int i = 0 ; i < n ; i++)
		if(d == a[i]) return true;
	return false; 
}
//ham kiem tra do thi co lien thong hay khong va cho ta mot thu tu sap xep de co so mau = k
//nhung theo theo thu tu nguoc lai Vn, Vn-1, ...V1
//ta chi thuc hien ham khi do thi nay KHONG chinh quy

//rat tô`i o day, sau khi hoc xong mon nay 1,5 nam, xem lai thay tre trau v
bool LienThong(Dinh* *P, int n, int *a){
	int DegMax = 0 , Position, d = 0 , i = 0 ;
	for(int j = 0 ; j < n ; j++)
		if( DegMax < P[j]->NeiBor.size() ) DegMax = P[j]->NeiBor.size();
	//tim mot dinh co bac <= DegMax-1	
	for(int j = 0 ; j < n ; j++)
		if(P[j]->NeiBor.size() <= DegMax - 1){
			Position = j ; break ;
		}
	a[d++] = P[Position]->Pos;
	while(i < d){
		int k = a[i] - 1;
		for(int j = 0 ; j < P[k]->NeiBor.size() ; j++)
			if(App(P[k]->NeiBor[j]->Pos, a, d) == false)
				a[d++] = P[k]->NeiBor[j]->Pos;//neu chua xuat hien dinh ke voi a[i] thi ta ghi vao mang
		i++;
	}
	return d == n;//Do Thi Lien Thong Neu Tat Ca Cac Dinh Dc Liet Ke Trong Mang	
}
//===============================================================================================================
void AddDinh(Canh c, Dinh* *P){
	int s = c.s, e = c.e ;
	P[s-1]->NeiBor.push_back(P[e-1]) ;//cho vao danh sach hang xom
	P[e-1]->NeiBor.push_back(P[s-1]) ;
}
//Ham Tao Tat Ca Cac Dinh Va Luu Danh Sach Cac Dinh Ke Voi No
void AddAllDinh(Canh *C, Dinh* *P, int m){
	for(int i = 0 ; i < m ; i++)
		AddDinh(C[i], P);	
}

void OutPut(Dinh* *P, int n, Canh *C, int m){
	cout << "\ngraph dothi\n{\n" ;
	for(int i = 0 ; i < n ; i++){
		cout << P[i]->Pos << "[fillcolor = " << Color[P[i]->NumOfColor] << ", style = filled];\n";
	}
	for(int i = 0 ; i < m ; i++)
		cout << C[i].s << " -- " << C[i].e << ";" << endl;
	cout << "}";
}

int main() {
	int n, m ;
	cout << "Nhap So Dinh : " ; cin >> n;
	cout << "Nhap So Canh : " ; cin >> m;
	Canh *C = new Canh[m];
	Dinh* *P = new Dinh* [n];
	int *a = new int[n];
	for(int i = 0; i < m ; i++){
		cout << "Canh Thu " << i + 1 << endl;
		cin >> C[i].s >> C[i].e ;
	}
	for(int i = 0; i < n ; i++){
		a[i] = 0; 
		P[i] = new Dinh; P[i]->Pos = i + 1 ;//Duyet Tham Lam Theo Thu Tu Mac Dinh 
	}
	AddAllDinh(C, P, m);//tao danh dach dinh
	if(ChinhQuy(P, n) == false){
		if(LienThong(P, n, a)){
			Dinh* *Q = new Dinh* [n];
			for(int i = 0 ; i < n ; i++){//lay thu tu dinh V1, V2 ,... Vn
				Q[i] = new Dinh;
				Q[i] = P[a[n - 1 - i]-1];//do mang a dang chua Vn, Vn-1,..V1
			}
			cout << "Do Thi Vua Lien Thong Vua Khong Chinh Quy";
			GreedyAlgorithm(Q, n);
			OutPut(Q, n, C, m);
		}
		else{
			cout << "Do Thi Khong Lien Thong";
			GreedyAlgorithm(P, n);
			OutPut(P, n, C, m);
		}
	}
	else{
		cout << "Do Thi Chinh Quy";
		GreedyAlgorithm(P, n);
		OutPut(P, n, C, m);
	}
	return 0;
}
