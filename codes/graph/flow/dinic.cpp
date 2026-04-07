/// Complexity: O(|E|*|V|^2)
/// Faster flow algorithm 
// to check if edge is saturated cap == 0   
typedef ll tf;
struct edge { int v; tf cap; int inv; tf flow; };
struct network {
  int n, s, t;
  vi lvl;
  vector<vector<edge>> g;
  network(int n) : n(n), lvl(n), g(n) {}
  void add_edge(int u, int v, tf c) {
    g[u].pb({v, c, g[v].size(), 0});
    g[v].pb({u, 0, g[u].size()-1,c});
    // The following line is for undirected graphs
    // g[v].push_back({u, c, g[u].size()-1, 0});
  }
  bool bfs() {
    fill(lvl.begin(), lvl.end(), -1);
    queue<int> q;
    lvl[s] = 0;
    for(q.push(s); q.size(); q.pop()) {
      int u = q.front();
      for(auto &e : g[u]) {
        if(e.cap > 0 && lvl[e.v] == -1) {
          lvl[e.v] = lvl[u]+1;
          q.push(e.v);
        }
      }
    }
    return lvl[t] != -1;
  }
  tf dfs(int u, tf nf) {
    if(u == t) return nf;
    tf res = 0;
    for(auto &e : g[u]) {
      if(e.cap > 0 && lvl[e.v] == lvl[u]+1) {
        tf pushed = dfs(e.v, min(nf, e.cap));
        res += pushed; nf -= pushed; e.cap -= pushed;
        g[e.v][e.inv].cap += pushed;
        g[e.v][e.inv].flow -= pushed;
        e.flow += pushed;
        if(nf == 0) return res;
      }
    }
    if(!res) lvl[u] = -1;
    return res;
  }
  tf max_flow(int so, int si, tf res = 0) {
    s = so; t = si;
    //replace max value
    while(bfs()) res += dfs(s, INT_MAX);
    return res;
  }
  //first find max flow
  vector<ii> minCut() {
    bfs();
    vector<ii> mc;
    forn(i, n) {
        if(lvl[i] == -1) continue;
        for(auto &e : g[i]) {
            if(lvl[e.v] == -1) {
                mc.pb({i, e.v});
            }
        }
    }
    return mc;
  }
  vi minVertexCover(int aSize, int bSize) {
        //min vertex cover in bipartite graph.
        //a group should be from [1, a]
        //b group should be from [a + 1, a + b]
        //bfs get As and Bs the other nodes are At and Bt
        //which are unreachable from s in residual graph
        //the the minVertexCover is At U Bs
        bfs();
        vi mvc;
        forn(i, n) {
            if(lvl[i] == -1 and i >= 1 and i <= aSize) {
                mvc.pb(i);
            }
            else if(lvl[i] != 1 and i >= aSize + 1 and i <= aSize + bSize){
                mvc.pb(i);
            }
        }
        return mvc;
    }
};
