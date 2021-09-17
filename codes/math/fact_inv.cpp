const ll M = 998244353;

int maxi = 200010;
ll F[200010], INV[200010], FI[200010];

void init(){
	F[0] = 1; forsn(i, 1, maxi) F[i] = F[i-1]*i %M;
	INV[1] = 1; forsn(i, 2, maxi) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
	FI[0] = 1; forsn(i, 1, maxi) FI[i] = FI[i-1]*INV[i] %M;
}
