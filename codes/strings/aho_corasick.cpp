struct vertex {
  map<char, int> next, go;
  int p, link;
  char pch;
  vector<int> leaf;
  vertex(int p = -1, char pch = '$'):p(p), pch(pch), link(-1){}
};
vector<vertex> t;
void aho_init() {
    t.clear(); t.pb(vertex());
}
void add_string(string& s, int id) {
    int v = 0;
    for(char c:s) {
        if(!t[v].next.count(c)) {
            t[v].next[c] = t.size();
            t.pb(vertex(v, c));
        }
        v = t[v].next[c];
    }
    t[v].leaf.pb(id);
}
int go(int v, char c);
int get_link(int v) {
    if(t[v].link < 0) 
        if(v == 0 or t[v].p == 0) t[v].link = 0;
        else t[v].link = go(get_link(t[v].p), t[v].pch);
    return t[v].link;
}
int go(int v, char c) {
    if(!t[v].go.count(c)) 
        if(t[v].next.count(c)) t[v].go[c] = t[v].next[c];
        else t[v].go[c] = v == 0 ? 0 : go(get_link(v), c);
    return t[v].go[c];
}
//vis should be of the size of t
void proc(int x) {
    if(x == -1 or vis[x]) return;
    vis[x] = true;
    //do something with the strings that were found
    forn(i, t[x].leaf.size()) {}
    proc(get_link(x));
}