typedef int T;
#define NEUT INF
T oper(T a, T b) {return min(a, b);}
struct STree { // persistent segment tree for min over integers
	vector<T> st; vi lc, rc; int n,sz,rt;
	STree(int n): st(1,NEUT),lc(1,0),rc(1,0),n(n),rt(0),sz(1){}
	int new_node(T v, int l=0, int r=0){
		int ks=st.size();
		st.pb(v);lc.pb(l);rc.pb(r);
		return ks;
	}
	int init(int l, int r, vector<T>& a){
		if(l==r)return new_node(a[l]);
		int m=(l + r)/2,lp=init(l,m,a),rp=init(m + 1,r,a);
		return new_node(oper(st[lp],st[rp]),lp,rp);
	}
	int upd(int p, int l, int r, int pos, T v){
		int np=new_node(st[p],lc[p],rc[p]);
		if(l==r){st[np]=v;return np;}
		int m=(l+r)/2,ps;
		if(pos<=m)ps=upd(lc[np],l,m,pos,v),lc[np]=ps;
		else ps=upd(rc[np],m+1,r,pos,v),rc[np]=ps;
		st[np]=oper(st[lc[np]],st[rc[np]]);
		return np;
	}
	int query(int p, int l, int r, int L, int R){
		if(R < l or r < L) return NEUT;
    if(L <= l and r <= R) return st[p];
		int m=(l+r)/2;
		return oper(query(lc[p],l,m,L,R),query(rc[p],m+1,r,L,R));
	}
	int init(vector<T>& a){return init(0,n - 1,a);}
	int upd(int p, int pos, T v){return rt=upd(p,0,n-1,pos,v);}
	int upd(int p, T v){return upd(rt,p,v);} // update on last root
	T query(int p, int L, int R){return query(p,0,n-1,L,R);}
}; // usage: STree rmq(n);root=rmq.init(x);new_root=rmq.upd(root,i,v);rmq.query(root,s,e);