ii toVect(ii a, ii b) {
    return{b.F - a.F, b.S - a.S};
} 
bool segmentIntersection(ii a, ii b, ii c, ii d){
    ll v1 = cross(toVect(c, a), toVect(c, b));
    ll v2 = cross(toVect(d, a), toVect(d, b));
    if((v1 < 0 and v2 < 0) or (v1 > 0 and v2 > 0)) {
        return false;
    }
    if(v1 == 0 and v2 == 0) {
        if((min(a.F, b.F) <= c.F and c.F <= max(a.F, b.F)) and
            (min(a.S, b.S) <= c.S and c.S <= max(a.S, b.S))) {
                return true;
            }
        if((min(a.x, b.x) <= d.x and d.x <= max(a.x, b.x)) and
            (min(a.y, b.y) <= d.y and d.y <= max(a.y, b.y))) {
                return true;
            }
        if((min(c.x, d.x) <= a.x and a.x <= max(c.x, d.x)) and
            (min(c.y, d.y) <= a.y and a.y <= max(c.y, d.y))) {
                return true;
            }
        if((min(c.x, d.x) <= b.x and b.x <= max(c.x, d.x)) and
            (min(c.y, d.y) <= b.y and b.y <= max(c.y, d.y))) {
                return true;
            }
        return false;
    }
    
    v1 = cross(toVect(a, c), toVect(a, d));
    v2 = cross(toVect(b, c), toVect(b, d));
    
    if((v1 < 0 and v2 < 0) or (v1 > 0 and v2 > 0)) {
        return false;
    }
    return true;
}
