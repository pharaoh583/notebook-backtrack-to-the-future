#define forn(i,n) for(int i = 0; i < int(n); i++)
const int mod = 1e9 + 7;
 
struct M{
	ll m[2][2];
	M(){
		m[0][0] = 0;
		m[0][1] = 1;
		m[1][0] = -1;
		m[1][1] = 1;
	}
	M(int a){
		m[0][0] = a;
		m[0][1] = a;
		m[1][0] = a;
		m[1][1] = a;
	}
	M operator * (M b){
		M aux = M(0);
		forn(i, 2){
			forn(j, 2){
				forn(k, 2){
					aux.m[i][j] += m[i][k] * b.m[k][j];
				}
			}
		}
		return aux;
	}
};
 
M exp(M a, int n){
	if(n == 1) return a;
	M z = exp(a, n/2);
	if(n%2 == 0) return z * z;
	return z * z * a;
}
