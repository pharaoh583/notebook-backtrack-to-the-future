vi s;
vi g[200001];
int n;
vector<bool> disabled;
int treeSize(int u, int p) {
    int sz = 1;
    for(auto v : g[u]) {
        if(v != p and !disabled[v]) {
            sz += treeSize(v, u);
        }
    }
    return s[u] = sz;
} 
int findCentroid(int u, int size) {
    for(auto v : g[u]) {
        if(disabled[v]) continue;
        if(s[v]*2 > size) {
            s[u] -= s[v];  
            return findCentroid(v, size);
        }
    }
    return u;
}
ll centroidDecomposition(int provRoot = 0) {
    int sz = treeSize(provRoot, provRoot);
    //TODO: check if you can end early based on size
    int centroid = findCentroid(provRoot, sz);
    ll res = 0;
    //TODO: implement logic to process centroid
    disabled[centroid] = true;
    //TODO: clear data if necessary
    return res;
}
//TODO: start disabled and s
