ll distSqrd(ii a, ii b) {
    return (ll)((a.F - b.F) * (ll)(a.F - b.F)) + (ll)((a.S - b.S) * (ll)(a.S - b.S));
} 
//return dist * dist, get sqrt for real dist
ll minEuclidDist(vector<ii> p) {
    sort(all(p));
    set<ii> s;
    ll minDistSqr = 8000000000000000001;
    ll minDistP1 = sqrt(minDistSqr) + 1;
    int l = 0;
    forn(i, p.size()) {
        auto it = s.lower_bound(mp((ll)p[i].S - minDistP1, 0LL));
        while(it != s.end() and it->F <= p[i].S + minDistP1) {
            ii pe = (*it);
            swap(pe.F, pe.S);
            ll nd = distSqrd(p[i], pe);
            if(nd < minDistSqr) {
                minDistSqr = nd;
                minDistP1 = sqrt(minDistSqr);
            }
            it++;
        }
        s.insert(mp(p[i].S, p[i].F));
        while(l < i) {
            if(abso(p[i].F - p[l].F) > minDistP1) {
                s.erase(mp(p[l].S, p[l].F));
                l++;
            }
            else break;
        }
    }
    return minDistSqr;
}
