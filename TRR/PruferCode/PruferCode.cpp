#include<iostream>

using namespace std ;

struct Canh{
	int DinhDau, DinhCuoi ;
};

void AddDeg(Canh *C, int *deg, int n){//ham tao bac cho cac dinh
	for(int i = 0 ; i < n ; i++){
		int c1 = C[i].DinhDau , c2 = C[i].DinhCuoi ;
		deg[c1]++ ; deg[c2]++ ;
	}
}

int DinhKe(Canh *C, int *deg, int Num, int *tick, int n){//Num la dinh bac 1
	for(int i = 0 ; i < n ; i++){
		int c1 = C[i].DinhDau , c2 = C[i].DinhCuoi ;
		if(c1 == Num && tick[i] ){
			deg[c1]-- ; deg[c2]--; tick[i] = 0 ;//danh dau la canh do da dung roi
			return c2 ;
		}
		if(c2 == Num && tick[i]  ){
			deg[c1]-- ; deg[c2]--; tick[i] = 0 ;
			return c1 ;
		}
	}
}

int d = 0 ;
void PruferCode( Canh *C, int *deg, int *tick, int i, int n){
	if(d < n-1 && i <= n){
			if(deg[i] == 1){
				int t = DinhKe(C, deg, i, tick, n) ;
				cout << t << " " ;
				d++;
				if(t < i && t) PruferCode(C, deg, tick, t, n); 
				else PruferCode(C, deg, tick, i+1, n) ;
			}
			else PruferCode(C, deg, tick, i+1, n) ;
	}
}

int main(){
	int n ; 
	cout << "Nhap so canh : " ; cin >> n ;
	Canh *C = new Canh[n] ; 
	int *deg = new int[n+1] ;
	int *tick = new int[n] ;
	for( int i = 0 ; i < n+1 ; i++) deg[i] = 0;
	for(int i = 0 ; i < n ; i++){
		cout << "Canh Thu " << i+1 << endl ;
		cin >> C[i].DinhDau >> C[i].DinhCuoi ;
		tick[i] = 1 ;
	}
	AddDeg(C, deg, n) ;
	cout << "\nPrufer_Code\n" ;
	PruferCode(C, deg, tick, 1, n) ;
	return 0 ;
}
