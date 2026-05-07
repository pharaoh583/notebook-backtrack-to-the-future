const ll M = 998244353;

int maxi = 200010;
ll F[200010], INV[200010], FI[200010];

void init(){
	F[0] = 1; forsn(i, 1, maxi) F[i] = F[i-1]*i %M;
	INV[1] = 1; forsn(i, 2, maxi) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
	FI[0] = 1; forsn(i, 1, maxi) FI[i] = FI[i-1]*INV[i] %M;
}

// works if gcd(A, M) = 1
int modInverse(int A, int M){
    int m0 = M;
    int y = 0, x = 1;

    if (M == 1) return 0;

    while (A > 1) {
        int q = A / M;
        int t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;

    return x;
}
