vi g[1<<K]; int n; //K such that 2^K >= n
int f[K][1<<K], d[1<<K];
void lca_dfs(int u) {
  for(auto v : g[u]) {
    if(v == f[0][u]) continue;
    f[0][v] = u, d[v] = d[u] + 1; lca_dfs(v);
  }
}
void lca_init() {
  d[0] = 0; f[0][0] = -1;
  lca_dfs(0);
  forsn(k, 1, K) forn(u, n) 
    if(f[k - 1][u] < 0) f[k][u] = -1;
    else f[k][u] = f[k - 1][f[k - 1][u]];
}
int lca(int x, int y) {
  if(d[x] < d[y]) swap(x, y);
  for(int k = K - 1; k >= 0; k--) if(d[x] - (1<<k) >= d[y]) x = f[k][x];
  if(x == y) return x;
  for(int k = K - 1; k >= 0; k--) if(f[k][x] != f[k][y]) x = f[k][x], y = f[k][y];
  return f[0][x];
}