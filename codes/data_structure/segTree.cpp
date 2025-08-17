#define NEUT INF
typedef int T;
T op(T a, T b) {return min(a, b);}
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
    T query(int p, int l, int r, int a, int b) { //query of [l, r]
        if(l > b or r < a) return NEUT;
        if(a <= l and r <= b) return st[p];
        int m = (l + r)/2;
        return oper(query(p<<1, l, m, a, b), query(p<<1|1, m + 1, r, a, b));
    }

    void init(vector<T>& a){init(1, 0, n - 1, a);}
    void upd(int p, T val) {upd(1, 0, n - 1, p, v);}
    T query(int a, int b) {return query(1, 0, n - 1, a, b);}
};