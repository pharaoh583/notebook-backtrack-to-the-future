struct DSU {
  vector<int> p, sz;
  void init(int N) { sz.assign(N, 1);
    p.resize(N); iota(all(p), 0); 
  }
  int get(int x) { 
    return x == p[x] ? x : p[x] = get(p[x]);
  }
  bool sameSet(int a, int b) { return get(a) == get(b); }
  int size(int x) { return sz[get(x)]; }
  bool unite(int x, int y) {  // union by size
    x = get(x), y = get(y); 
    if (x == y) return false;
    if (sz[x] < sz[y]) swap(x, y);
    p[y] = x; sz[x] += sz[y]; 
    return true;
  }
};