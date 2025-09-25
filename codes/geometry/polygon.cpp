int sgn(double x){return x < -EPS?-1:X > EPS;}
struct pol{
    int n; vector<pt> p;
    pol() {}
    pol(vector<pt> _p) {p = _p; n = p.size();}
    double area() {
        double r = 0.;
        forn(i, n) r += p[i]%p[(i + 1)%n];
        return abs(r)/2;
    }
    pt centroid() {
        pt r(0, 0); double t = 0;
        forn(i n) {
            r = r + (p[i] + p[(i + 1)%n])*(p[i]%p[(i + 1)%n]);
            t += p[i]%p[(i + 1)%n];
        }
        return r/t/3;
    }
    bool has(pt q) { //O(n)
        forn(i, n) if(ln(p[i], p[(i+1)%n]).seghas(q)) return true;
        int cnt = 0;
        forn(i, n) {
            int j = (i + 1)%n;
            int k = sgn((q-p[j])%(p[i]-p[j]));
            int u = sgn(p[i].y-q.y), v=sgn(p[j].y-q.y);
            if(k > 0 and u < 0 and v >= 0) cnt++;
            if(k < 0 and v < 0 and u >= 0) cnt--;
        }
        return cnt != 0;
    }
    bool haslog(pt q) { //O(log(n)) only CONVEX, call normalize first
        if(q.left(p[0], p[1]) or q.left(p.back(), p[0])) return false;
        int a = 1, b = p.size() - 1;
        while(b - a > 1) {
            int c = (a + b)/2;
            if(!q.left(p[0], p[c]))a = c;
            else b = c;
        }
        return !q.left(p[a], p[a + 1]);
    }
    pt farthest(pt v) {
        if(n < 10) {
            int k = 0;
            forsn(i, 1, n) if(v * (p[i]-p[k]) > EPS) k = i;
            return p[k];
        }
        if(n == p.size()) p.pb(p[0]);
        pt a = p[1] - p[0];
        int s = 0, e = n, ua = v*a > EPS;
        if(!ua and v*(p[n - 1] - p[0]) <= EPS) return p[0];
        while(true) {
            int m = (s + e)/2; pt c = p[m + 1] - p[m];
            int uc = v * c > EPS;
            if(!uc and v * (p[m - 1]-p[m])<=EPS) return p[m];
            if(ua and (!uc or v * (p[s]-p[m]) > EPS)) e=m;
            else if(ua or uc or v * (p[s]-p[m]) >= -EPS) s=m, a=c, ua=uc;
            else e=m;
            assert(e > s + 1);
        }
    }
    pol cut(ln l) { //cut CONVEX polygon by line l
        vector<pt> q;
        forn(i, n) {
            int d0 = sgn(l.pq%(p[i]-l.p)), d1=sgn(l.pq%(p[(i+1)%n]-l.p));
            if(d0>=0) q.pb(p[i]);
            ln m(p[i], p[(i + 1)%n]);
            if(d0*d1 < 0 and !(l/m))q.pb(l^m);
        }
        return pol(q);
    }
    double callipers() { //square distance of most distant points
        double r = 0;
        for(int i = 0, j = n < 2 ? 0 : 1; i < j; ++i) {
            for(;;j=(j + 1)%n) {
                r = max(r, (p[i] - p[j]).norm2());
                if((p[(i + 1)%n]-p[i])%(p[(j + 1)%n]-p[j]) <= EPS) break;
            }
        }
        return r;
    }
};

vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	forn(i,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}
//Dynamic convex hull trick
vector<pol> w;
void add(pt q) { //add(q), O(log^2(n))
    vector<pt> p={q};
    while(!w.empty() and w.back().p.size() < 2*p.size()) {
        for(pt v : w.back().p) p.pb(v);
        w.pop_back();
    }
    w.pb(pol(chull(p)));
}
ll query(pt v) {
    ll r = -INF;
    for(auto& p : w) r = max(r, p.farthest(v) * v);
    return r;
}