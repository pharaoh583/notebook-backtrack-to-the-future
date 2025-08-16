#define RB(x) (x < n ? r[x] : 0)
 
void csort(vi& sa, vi& r, int k) {
    int n = sa.size();
    vi f(max(255, n), 0), t(n);
    forn(i, n) f[RB(i + k)]++;
    int sum  = 0;
    forn(i, max(255, n)) f[i] = (sum += f[i]) - f[i];
    forn(i, n) t[f[RB(sa[i] + k)]++] = sa[i];
    sa = t;
}
 
vi constructSA(string& s) { //O(nlogn)
    int n = s.size(), rank;
    vector<int> sa(n), r(n), t(n);
    forn(i, n) sa[i] = i, r[i] = s[i];
    for(int k = 1; k < n; k *= 2) {
        csort(sa, r, k); csort(sa, r, 0);
        t[sa[0]] = rank = 0;
        for(int i = 1; i < n; i++) {
            if(r[sa[i]] != r[sa[i - 1]] or RB(sa[i] + k) != RB(sa[i - 1] + k)) rank++;
            t[sa[i]] = rank;
        }
        r = t;
        if (r[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

vector<int> computeLCP(string& s, vector<int>& sa){
	int n=s.size(),L=0;
	vector<int> lcp(n),plcp(n),phi(n);
	phi[sa[0]]=-1;
	forsn(i,1,n)phi[sa[i]]=sa[i-1];
	forn(i,n){
		if(phi[i]<0){plcp[i]=0;continue;}
		while(s[i+L]==s[phi[i]+L])L++;
		plcp[i]=L;
		L=max(L-1,0);
	}
	forn(i,n)lcp[i]=plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}
 
int patternMatching(string& s1, string& s2, vi& sa) { //O(s1log(s2))
    if (s2.size() < s1.size()) {
        return 0;
    }
    int result_start = 0, result_end = s2.size() - 1;
    forn(i, s1.size()) {
        int start = lower_bound(sa.begin() + result_start, sa.begin() + result_end + 1, s1[i], [&](int idx, char b) {
            return idx + i >= s2.size() || s2[idx + i] < b;
        }) - sa.begin();
        if (start > result_end || (s2[sa[start] + i]) != s1[i]) {
            return 0;
        }
        int end = upper_bound(sa.begin() + result_start, sa.begin() + result_end + 1, s1[i], [&](char b, int idx) {
            return idx + i < s2.size() && s2[idx + i] > b;
        }) - sa.begin() - 1;
        result_start = start;
        result_end = end;
    }
    return result_end - result_start + 1;
}