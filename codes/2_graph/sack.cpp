//TODO: define maxn
vi g[maxn];

int timer = 0;
int sz[maxn], st[maxn], ft[maxn], ver[maxn];
void preDfs(int u, int p = -1) {
    ver[timer] = u, sz[u] = 1, st[u] = timer++;   
    for(auto v : g[u]) if(v != p) {
        preDfs(v, u);
        sz[u] += sz[v];
    }
    ft[u] = timer;
}
//add stlm data structure and init

//TODO: implement addElement
//TODO: implement removeElement
//TODO: implement getAns
//TODO: implement cleanup
void dfs(int u, int p = -1, bool keep = false) {
    int mx = -1, bigChild = -1;
    for(auto v : g[u]) if(v != p and sz[v] > mx) {
        mx = sz[v], bigChild = v;
    }

    for(auto v : g[u]) if(v != p and v != bigChild) {
        dfs(v, u, 0);
    }
    if(bigChild != -1) dfs(bigChild, u, 1);

    for(auto v : g[u]) if(v != p and v != bigChild) {
        for(int i = st[v]; i < ft[v]; i++) addElement(val[ver[i]]);
    }
    addElement(val[u]);
    res[u] = getAns();

    if(!keep) {
        for(int i = st[u]; i < ft[u]; i++) removeElement(val[ver[i]]);
        cleanup();
    }
}
