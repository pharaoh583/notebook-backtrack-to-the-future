int sgn2(double x){return x < 0?  -1 : 1;}
struct ln{
    pt p, pq;
    ln(pt p, pt q) : p(p), pq(q - p) {}
    ln() {}
    bool has(pt r) {return dist(r) <= EPS;}
    bool seghas(pt r) {return has(r) and (r - p) * (r - (p + pq)) <= EPS;}
    bool operator/(ln l) {return abs(pq.unit()%l.pq.unit())<=EPS;}
    bool operator==(ln l) {return *this/l and has(l.p);}
    pt operator^(ln l) { //intersection
        if(*this/l) return pt(DINF, DINF);
        pt r = l.p + l.pq * ((p -l.p)%(l.pq%pq));
        return r;
    }
    double angle(ln l) {return pq.angle(l.pq);}
    int side(pt, r) {return has(r)?0:sgn2(pq%(r-p));} 
    pt proj(pt r) {return p + pq*((r-p)*pq/pq.norm2());}
    pt ref(pt r) {return proj(r)*2 - r;}
    double dist(pt r) {return (r-proj(r)).norm();}
    ln rot(auto a) {return ln(p, p+pq.rot(a));}
};
ln bisector(ln a, ln m) { //angle bisector
    pt p = l^m;
    return ln(p, p+l.pq.unit()+m.pq.unit());
}
ln bisector(pt p, pt q) { // segment bisector
    return ln((p+q)*.5, p).rot(ccw90);
}