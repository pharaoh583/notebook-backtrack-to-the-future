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

int wh[maxn+2][maxc]; //wh[i][j] = a donde vuelvo si estoy en i y pongo una j 
void prefix_automaton(string &s){ 
    int lps=0; 
    forn(j,maxc) wh[0][j]=0; 
    wh[0][s[0]-'A'] = 1; 
    forsn(i,1,s.size()+1){ 
        forn(j,maxc) wh[i][j]=wh[lps][j]; 
        if(i<s.size()){ 
            wh[i][s[i]-'A'] = i+1; 
            lps = wh[lps][s[i]-'A']; 
        } 
    }
}
