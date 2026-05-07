struct vertex {
    int freq, p;
    char val;
    map<char, int> next;
    vertex(char val = '$', int freq = 0, int link = -1, int p = -1) : val(val), freq(freq), link(link), p(p) {}
};

vector<vertex> t; 
void init() {
    t.pb(vertex());
}
void add_string(string& s) {
    int v = 0;
    for(auto c : s) {
        if(!t[v].next.count(c)) {
            t[v].next[c] = t.size();
            t.pb(vertex(c, 0, -1, v));
        }
        v = t[v].next[c];
    }
    t[v].freq++;
}