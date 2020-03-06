#include<iostream>
#include<Set> // thu vien hoat dong nhu cay nhi phan
 
using namespace std ;
typedef set<int> Btree ;

struct Canh{
	int DinhDau, DinhCuoi ;
};

void GhiBtree(Canh *C, Btree *l, int SoCanh){
	for(int i = 0 ; i < SoCanh ; i++){
		int s = C[i].DinhDau  , e = C[i].DinhCuoi ;
		l[s].insert(e) ;//hai dong dung de luu cac dinh ke voi dinh dang xet
		l[e].insert(s) ; // giong nhu bieu dien do thi bang danh sach ke
	}
}

int d = 1 ;
void PruferCode(Btree *l, int i, int n){
	if(i < n && d <= n-2 ){ //ta chi hien thi n-2 canh
		if(l[i].size() == 1){//neu trong danh sach dinh ke co dung mot dinh
			int t = *l[i].begin() ;
			cout << t << " " ;
			d++ ;
			l[i].clear() ;//xoa dinh do ra
			l[t].erase(i)  ;//xoa dinh i trong danh sach ke voi dinh t
			if( l[t].size() == 1 && t) PruferCode(l, t, n);
			else PruferCode(l, i+1, n) ;
		}
		else PruferCode(l, i+1, n) ;
	}
}

int main(){
	int n  ; 
	cout << "Nhap So Dinh : " ; cin >> n ;
    Btree *l  = new Btree[n] ;
	Canh *C = new Canh[n-1] ;
	for( int i = 0 ; i < n-1 ; i++ ){
		cout << "Nhap Canh Thu " << i+1 << endl ;
		cin >> C[i].DinhDau >> C[i].DinhCuoi ; 
	}
	GhiBtree(C,l,n-1) ;
	cout << "\n\nPrufer Code\n" ;
	PruferCode(l,1,n);
	delete []l ;
	delete []C ;
	return 0 ;
}
