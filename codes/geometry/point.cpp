#define EPS 1e-9

double fabso(double x){
	return (x < 0.000000000)? -x:x;
}

struct P{
	double x, y;
	void read(){
		cin>>x>>y;
	}
	P operator - (P b) const{
		return P{x - b.x, y - b.y};
	}
	void operator -= (P b){
		x -= b.x;
		y -= b.y;
	}
	P operator + (P b) const{
		return P{x + b.x, y - b.y};
	}
	void operator += (P b){
		x += b.x;
		y += b.y;
	}
	double operator *(P b){
		return x * b.y - y * b.x;
	}
	bool operator == (P other) const{
		return (fabso(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
};
double cross(P a, P b){
	return a.x * b.y - b.x * a.y;
}

bool ccw(P p, P q, P r){
	return cross(q - p, r - p) < 0.000000000;
}
