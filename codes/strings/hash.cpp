hash p[2001][2];
const int maxn = 2001;
hash B = 37;
string t; 
hash h[2001][2];
const hash L = 1000000901LL;
//const hash L = 1e9 + 7;
const hash L2 = 1e9 + 9;
const char startAlpha = 'a';
hash V(char a){
	return (hash)(a - startAlpha + 1);
}

void init(){
	p[0][0] = p[0][1] = 1LL;
	forsn(i, 1, maxn){
		p[i][0] = (p[i - 1][0] * B)%L;	
		p[i][1] = (p[i - 1][1] * B)%L2;
	}
	h[0][0] = h[0][1] = 0LL;
	int n = t.size();
	forsn(i, 1, n + 1){
		h[i][0] = ((h[i - 1][0] * B)%L + V(t[i - 1]))%L;
		h[i][1] = ((h[i - 1][1] * B)%L2 + V(t[i - 1]))%L2;
	}

}

pair<hash, hash> Hash(string a){
	pair<hash, hash> hs = mp(0LL, 0LL);
	forn(i, a.size()){
		hs.F = ((hs.F * B)%L + V(a[i]))%L;
		hs.S = ((hs.S * B)%L2 + V(a[i]))%L2;
	}
	return hs;
}

pair<hash, hash> hashCalc(int a, int b){
	return mp((h[b][0] - (p[b - a][0] * h[a][0])%L + L)%L, (h[b][1] - (p[b - a][1] * h[a][1])%L2 + L2)%L2);
}

vi KMP(string s){ //not quite but does the same
	int n = s.size();
	vi pos;
	pair<hash, hash> hs = Hash(s);
	forn(i, t.size() + 1 - n){
		pair<hash, hash> sub = hashCalc(i, i + n);
		if(sub.F == hs.F and sub.S == hs.S) pos.pb(i);
	}
	return pos;
}

