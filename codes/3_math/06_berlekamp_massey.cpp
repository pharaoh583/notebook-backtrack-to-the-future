vi BM(vi x){
	vi ls,cur;int lf,ld;
  forn(i,x.size()){
		ll t=0;
    forn(j,cur.size())t=(t+x[i-j-1]*(ll)cur[j])%MOD;
		if((t-x[i])%MOD==0)continue;
    if(!cur.size()){cur.resize(i+1);lf=i;ld=(t-x[i])%MOD;continue;}
		ll k=-(x[i]-t)*fast_pow(ld,MOD-2)%MOD;
		vi c(i-lf-1);c.pb(k);
    forn(j,ls.size())c.pb(-ls[j]*k%MOD);
    if(c.size()<cur.size())c.resize(cur.size());
    forn(j,cur.size())c[j]=(c[j]+cur[j])%MOD;
    if(i-lf+ls.size()>=cur.size())ls=cur,lf=i,ld=(t-x[i])%MOD;
		cur=c;
	}
  forn(i,cur.size())cur[i]=(cur[i]%MOD+MOD)%MOD;
	return cur;
}
