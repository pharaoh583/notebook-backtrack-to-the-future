//this example supports range sum queries, range updates [l,r] = x and 
//range sum updates [l,r] += x
class SegTree {
private:
    int n;
    vi t, a;
    vi lazyUpd, lazySum;
    void build(int p, int L, int R) {
        if(L == R) {
            t[p] = a[L];
            return;
        }
        
        int m = (L + R)/2;
        build(p<<1, L, m); build(p<<1|1, m + 1, R);
        
        t[p] = t[p<<1] + t[p<<1|1];
    }
    
    void push(int p, int L, int R) {
        if(L == R) {
            if(lazyUpd[p] != -1) {
                t[p] = lazyUpd[p];
            }
            t[p] += lazySum[p];
            lazyUpd[p] = -1; lazySum[p] = 0;
            return;
        }
        
        if(lazyUpd[p] != -1) {
            t[p] = lazyUpd[p] * (R - L + 1);
            lazyUpd[p<<1] = lazyUpd[p<<1|1] = lazyUpd[p];
            lazyUpd[p] = -1;
            lazySum[p<<1] = lazySum[p<<1|1] = 0;
        }
        t[p] += lazySum[p] * (R - L + 1);
        lazySum[p<<1] += lazySum[p];
        lazySum[p<<1|1] += lazySum[p];
        lazySum[p] = 0;
    }
    
    ll query(int p, int L, int R, int l, int r) {
        // cout<<p<<" "<<L<<" "<<R<<" "<<l<<" "<<r<<el;
        if(l > r) return 0;
        push(p, L, R);
        if(l <= L and R <= r) return t[p];
        int m = (L + R)/2;
        return query(p<<1, L, m, l, min(r, m)) +
               query(p<<1|1, m + 1, R, max(l, m + 1), r);
    }
    
    void update(int p, int L, int R, int l, int r, int v) {
        if(l > r) return;
        
        push(p, L, R);
        if(l <= L and R <= r) {
            lazyUpd[p] = v; lazySum[p] = 0; return;
        }
        
        int m = (L + R)/2;
        update(p<<1, L, m, l, min(m, r), v);
        update(p<<1|1, m + 1, R, max(m + 1, l), r, v);
        
        push(p<<1, L, m);
        push(p<<1|1, m + 1, R);
        t[p] = t[p<<1] + t[p<<1|1];
    }
    
    void sum(int p, int L, int R, int l, int r, int v) {
        if(l > r) return;
        
        push(p, L, R);
        if(l <= L and R <= r) {
            lazySum[p] += v; return;
        }
        
        int m = (L + R)/2;
        sum(p<<1, L, m, l, min(m, r), v);
        sum(p<<1|1, m + 1, R, max(m + 1, l), r, v);
        
        push(p<<1, L, m);
        push(p<<1|1, m + 1, R);
        t[p] = t[p<<1] + t[p<<1|1];
    }
public: 
    SegTree(int n) : n(n), t(4 * n, 0), lazySum(4 * n, 0), 
    lazyUpd(4 * n, -1) { }
    SegTree(vi A) : SegTree(A.size()) {
        a = A;
        build(1, 0, n - 1);
    }
    
    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    
    void update(int l, int r, ll v) {
        update(1, 0, n - 1, l, r, v);
    }
    
    void sum(int l, int r, ll v) {
        sum(1, 0, n - 1, l, r, v);
    }
    
    void debug() {
        forsn(i, 1, t.size()) cout<<t[i]<<" "; cout<<el;
        forsn(i, 1, lazyUpd.size()) cout<<lazyUpd[i]<<" "; cout<<el;
        forsn(i, 1, lazySum.size()) cout<<lazySum[i]<<" "; cout<<el;
    }
};
