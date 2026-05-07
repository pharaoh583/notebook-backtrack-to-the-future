//TODO implement cross product
bool pointInLine(ii a, ii s, ii ed) {
    ii l = ii(s.F - a.F, s.S - a.S);
    ii r = ii(ed.F - a.F, ed.S - a.S);
    if(cross(l, r) == 0 and min(s.F, ed.F) <= a.F and a.F <= max(s.F, ed.F)
        and min(s.S, ed.S) <= a.S and a.S <= max(s.S, ed.S)) 
        return true;
    return false;
}
//0 -> outside, 1 -> inside, 2 -> boundary
int insidePoly(vector<ii> poly, ii point) {
    poly.pb(poly[0]);
    int cont = 0;
    forn(i, poly.size() - 1) {
        if(pointInLine(point, poly[i], poly[i + 1])) return 2;
        if(poly[i].F <= point.F and point.F < poly[i + 1].F) {
            ii l = ii(poly[i].F - point.F, poly[i].S - point.S);
            ii r = ii(poly[i + 1].F - point.F, poly[i + 1].S - point.S);
            if(cross(l, r) < 0) cont++;
        }
        else if(poly[i + 1].F <= point.F and point.F < poly[i].F) {
            ii r = ii(poly[i].F - point.F, poly[i].S - point.S);
            ii l = ii(poly[i + 1].F - point.F, poly[i + 1].S - point.S);
            if(cross(l, r) < 0) cont++;
        }
    }
    if(cont%2 == 0) return 0;
    return 1;
}
