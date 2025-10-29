#define NEUT INF
typedef int T;
T oper(T a, T b) {return min(a, b);}
struct STree {
    vector<T> st; int n;
    STree(int n) : st(4 * n + 5, NEUT), n(n) {}
    void init(int p, int l, int r, vector<T>& a) {
        if(l == r) {st[p]=a[l]; return;}
        int m = (l+r)/2;
        init(p<<1, l, m, a); init(p<<1|1, m + 1, r, a);
        st[p] = oper(st[p<<1], st[p<<1|1]);
    }
    void upd(int p, int l, int r, int pos, T val) {
        if(l == r) {st[p] = val; return;}
        int m = (l + r)/2;
        if(pos <= m) upd(p<<1, l, m, pos, val);
        else upd(p<<1|1, m + 1, r, pos, val);
        st[p] = oper(st[p<<1], st[p<<1|1]);
    }
    T query(int p, int l, int r, int L, int R) { //query of [l, r]
        if(R < l or r < L) return NEUT;
        if(L >= l and r <= R) return st[p];
        int m = (l + r)/2;
        return oper(query(p<<1, l, m, L, R), query(p<<1|1, m + 1, r, L, R));
    }

    void init(vector<T>& a){init(1, 0, n - 1, a);}
    void upd(int p, T val) {upd(1, 0, n - 1, p, val);}
    T query(int L, int R) {return query(1, 0, n - 1, L, R);}
};
