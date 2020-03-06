#include<iostream>
#include<queue>
#include<vector>
#define oo 100000000
#define NIL -1

using namespace std ;

//thuat toan dijkstra su dung hang doi uu tien, tu mot dinh s, hien thi duong di ngan nhat tu s toi u, voi u la diem 
//ma s toi duoc
struct Dist {
	int pos, distance;
};

struct Top  {
	int dist, par, pos;
	vector<Dist> near; //danh sach cac canh ke cung voi khoang cach tu diem dang xet voi canh ke
};

typedef Top* top;
typedef vector<top> Graph;

top init(int pos) {
	top p = new Top;
	p->pos = pos;
	p->par = NIL;
	p->dist = oo;
	return p;
}

struct cmp_dist {
	bool operator() (const top &a, const top &b) {
		return a->dist < b->dist;
	}
};

void dijkstra(Graph &G, top &s) {
	for(int i = 0 ; i < G.size() ; i++) {
		G[i]->dist = oo;
		G[i]->par = NIL;
	}
	s->dist = 0;
	//khoi tao hang doi uu tien luu cac diem co do uu tien theo dist nho hon
	priority_queue <top, vector<top>, cmp_dist > que;
	que.push(s);
	while(que.empty() == false) {
		top u = que.top();
		que.pop(); //xoa phan tu do dist nho nhat
		for(int i = 0 ; i  < u->near.size() ; i++) {
			int index = u->near[i].pos;
			int dis = u->near[i].distance;
			if(G[index]->dist > u->dist + dis) {
				G[index]->dist = u->dist + dis;
				G[index]->par = u->pos; //cat nhat lai dinh phia truoc
				que.push(G[index]);//day vo hang oi uu tien
			}
		}
	} 
}

int main(){
	return 0;
}

