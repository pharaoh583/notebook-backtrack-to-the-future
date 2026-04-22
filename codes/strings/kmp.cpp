vi prefix_function(string s) {
    int n = s.size();
    vi pi(n);
    forsn(i, 1, n) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
void compute_automaton(string s, vector<vi>& aut) {
    s += '#';
    int n = s.size();
    vi pi = prefix_function(s);
    aut.assign(n, vi(26));
    forn(i, n) {
        forn(j, 26) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
