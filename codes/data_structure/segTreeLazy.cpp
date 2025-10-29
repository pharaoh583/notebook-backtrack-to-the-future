#define NEUT 0
typedef int T;
T oper(T a, T b) {return a + b;}
struct STree { // example: range sum with range addition
	vector<T> st,lazy;int n;
	STree(int n): st(4*n+5,NEUT), lazy(4*n+5,NEUT), n(n) {}
	void init(int p, int l, int r, vector<T>& a){
		lazy[p]=0;  // lazy neutral element
		if(l==r){st[p]=a[l];return;}
		int m=(l+r)/2;
		init(p<<1,l,m,a);init(p<<1|1,m+1,r,a);
		st[p]=oper(st[p<<1],st[p<<1|1]);
	}
	void push(int p, int l, int r){
		if(!lazy[p])return; // if neutral, nothing to do
		st[p]+=(r-l+1)*lazy[p]; // update st according to lazy
		if(l<r){ // propagate to children
			lazy[p<<1]+=lazy[p];
			lazy[p<<1|1]+=lazy[p];
		}
		lazy[p]=0; // clear node lazy
	}
	void upd(int p, int l, int r, int L, int R, T v){
		push(p,l,r);
		if(R < l or r < L)return; //breakCondition() change for segTree beats
		if(L<=l and r<=R){ //tagCondition()
			lazy[p]+=v; // accumulate lazy
			push(p,l,r);return;
		}
		int m=(l+r)/2;
		upd(p<<1,l,m,L,R,v);upd(p<<1|1,m + 1,r,L,R,v);
		st[p]=oper(st[p<<1],st[p<<1|1]); // updateOperation()
	}
	T query(int p, int l, int r, int L, int R){ //supports [l, r] operations
		if(R < l or r < L)return NEUT; // operation neutral
		push(p,l,r);
		if(L<=l and r<=R)return st[p];
		int m=(l+r)/2;
		return oper(query(p<<1,l,m,L,R),query(p<<1|1,m+1,r,L,R)); // operation
	}
	void init(vector<T>& a){init(1,0,n - 1,a);}
	void upd(int L, int R, T v){upd(1,0,n - 1,L,R,v);}
	T query(int L, int R){return query(1,0,n - 1,L,R);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(s,e,v);rmq.query(s,e);