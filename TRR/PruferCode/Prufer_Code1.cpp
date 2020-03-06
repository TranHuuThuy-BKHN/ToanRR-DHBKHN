#include<iostream>
#include<List>
using namespace std ;
typedef list<int> DSLK ;
struct Canh{
	int DinhDau , DinhCuoi ;
};
void GhiList( Canh *C , DSLK *l , int SoCanh ){
	for( int i = 0 ; i < SoCanh ; i++ ){
		int s = C[i].DinhDau  , e = C[i].DinhCuoi ;
		l[s].push_back(e) ;
		l[e].push_back(s) ;
	}
}
void PruferCode( DSLK *l , int i , int n ){
	if( i < n ){
		if( l[i].size() == 1 ){
			int t = *l[i].begin() ;
			if(t) cout << t << " " ;
			l[i].clear() ;
			l[t].remove(i) ;
			if( l[t].size() == 1 ) PruferCode(l,t,n);
			else PruferCode(l,i+1,n) ;
		}
		else PruferCode(l,i+1,n) ;
	}
}
int main(){
	int n ; 
	cout << "Nhap So Dinh : " ; cin >> n ;
	DSLK *l  = new DSLK[n] ;
	Canh *C = new Canh[n-1] ;
	for( int i = 0 ; i < n-1 ; i++ ){
		cout << "Nhap Canh Thu " << i+1 << endl ;
		cin >>C[i].DinhDau >> C[i].DinhCuoi ; 
	}
	GhiList(C,l,n-1) ;
	cout << "\n\nPrufer Code\n" ;
	PruferCode(l,1,n);
	delete []l ;
	delete []C ;
	return 0 ;
}
