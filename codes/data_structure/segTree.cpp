class SegTree {
private:
    int n;
    vi A, t;
    
    void build() {
        forn(i, n) {
            t[i + n] = A[i];
        }
        
        for(int i = n - 1; i > 0; i--) {
            t[i] = t[i<<1] + t[i<<1|1];
        }
    }
    
public:
    SegTree(int sz) : n(sz), t(2 * sz) {}
    SegTree(const vi &initA) : SegTree((int)initA.size()) {
        A = initA;
        build();
    }
    
    ll RSQ(int l, int r) {
        ll tot = 0;
        for(l += n, r += n; l < r; l>>=1, r>>=1) {
            if(l&1) tot += t[l++];
            if(r&1) tot += t[--r];
        }
        return tot;
    }
    
    void update(int pos, int val) {
        for(t[pos += n] = val; pos > 1; pos >>=1) t[pos>>1] = t[pos] + t[pos^1];
    }
    
    void print() {
        forn(i,2 * n) {
            cout<<t[i]<<" ";
        } cout<<el;
    }
};
//code from https://codeforces.com/blog/entry/18051
