int n, m; 
const int MAXN = 1000;
int a[MAXN][MAXN], st[2*MAXN][2*MAXN];
#define NEUT 0
int oper(int a, int b) {return a + b;}
void build() {
    forn(i, n) forn(j, m) st[i + n][j + m] = a[i][j];
    forn(i, n) for(int j = m - 1; j; --j)
        st[i + n][j] = oper(st[i + n][j<<1], st[i + n][j<<1|1]);
    for(int i = n - 1; i; --i) forn(j, m<<1) {
        st[i][j] = oper(st[i<<1][j], st[i<<1|1][j]);
    }
}
void upd(int r, int c, int v){
    st[r + n][c + m] = v;
    for(int j = c + m; j > 1; j>>=1) st[r + n][j>>1]=oper(st[r + n][j], st[r + n][j^1]);
    for(int i = r + n; i > 1; i>>=1) for(int j = c + m; j; j>>=1)
        st[i>>1][j]=oper(st[i][j], st[i^1][j]);
}
//query of [r0, r1), [c0, c1)
int query(int r0, int r1, int c0, int c1) {
    int r = NEUT;
    for(int i0 = r0 + n, i1 = r1 + n; i0 < i1; i0>>=1, i1>>=1) {
        int t[4], q = 0;
        if(i0&1) t[q++]=i0++;
        if(i1&1) t[q++]=--i1;
        forn(k, q) for(int j0 = c0 + m, j1 = c1 + m; j0 < j1; j0>>=1, j1>>=1) {
            if(j0&1) r=oper(r, st[t[k]][j0++]);
            if(j1&1) r=oper(r, st[t[k]][--j1]);
        }
    }
    return r;
}