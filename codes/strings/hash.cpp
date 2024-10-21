struct Hash {
	int P=1777771, MOD[2], PI[2];
	vector<int> h[2],pi[2];
	Hash(string& s){
		MOD[0]=999727999; MOD[1]=1070777777;
		PI[0]=325255434; PI[1]=10018302;
		forn(k,2) h[k].resize(s.size()+1), pi[k].resize(s.size()+1);
		forn(k,2){
			h[k][0]=0;pi[k][0]=1;
			ll p=1;
			forsn(i,1,s.size()+1){
				h[k][i]=(h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
	}
   	 // get hash of range [s, e] indexed from 0 to n - 1
	ll get(int s, int e){
	    	e++;
		ll h0=(h[0][e]-h[0][s]+MOD[0])%MOD[0];
		h0=(1LL*h0*pi[0][s])%MOD[0];
		ll h1=(h[1][e]-h[1][s]+MOD[1])%MOD[1];
		h1=(1LL*h1*pi[1][s])%MOD[1];
		return (h0<<32)|h1;
	}
};


//this hash is slower but more accurate
#define bint __int128
struct Hash {
	bint MOD=212345678987654321LL,P=1777771,PI=106955741089659571LL;
	vector<bint> h,pi;
	Hash(string& s){
		assert((P*PI)%MOD==1);
		h.resize(s.size()+1);pi.resize(s.size()+1);
		h[0]=0;pi[0]=1;
		bint p=1;
		forsn(i,1,s.size()+1){
			h[i]=(h[i-1]+p*s[i-1])%MOD;
			pi[i]=(pi[i-1]*PI)%MOD;
			p=(p*P)%MOD;
		}
	}
	//get hash of range [s, e] indexed from 0 to n - 1
	ll get(int s, int e){
		e++;
		return (((h[e]-h[s]+MOD)%MOD)*pi[s])%MOD;
	}
};
