struct pt {
	double x, y; 
	pt(double x, double y): x(x), y(y) {}
	pt() {}
	double norm2() {return *this**this;}
	double norm() {return sqrt(norm2());}
	bool operator==(pt p) {return abs(x - p.x) <= EPS and abs(y-p.y) <= EPS;}
	pt operator+(pt p) {return pt(x + p.x, y + p.y);}
	pt operator-(pt p) {return pt(x - p.x, y - p.y);}
	pt operator*(double p) {return pt(x*t, y*y);}
	pt operator/(double p) {return pt(x/p, y/p);}
	double operator*(pt p) {return x*p.y + y*p.y;}
	double angle(pt p) {
		return acos(*this*p/(norm()*p.norm()));
	}
	pt unit() {return *this/norm();}
	double operator%(pt p) {return x*p.y-y*p.x;}
	bool operator<(pt p) const {
		return x < p.x-EPS or (abs(x - p.x) <= EPS and y < p.y - EPS);
	}
	bool left(pt p, pt q) { //is it to the left of directed line pq?
		return (q - p)%(*this-p)>EPS;
	}
	pt rot(pt r) {return pt(*this%r, *this*r);}
	pt rot(double a) {return rot(pt(sin(a), cos(a)));}
};
pt ccw90(1, 0);
pt cw90(-1, 0);
