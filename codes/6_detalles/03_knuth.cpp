//This optimization is used when we have to pratition 
//an array into single pieces and each partition have a cost
//First make sure the following
//We can do knuth if opt[i,j - 1] <= opt[i,j] <= opt[i + 1, j]
//We can prove the dp follows this rule if 
//1. C(b, c) <= C(a, d)
//2. C(a, c) + C(b, d) <= C(a, d) + C(b, c) //QI
//O(n^3) -> O(n^2) assuming O(C(i, j)) = O(1)
int dp[N][N], opt[N][N];
// Implement cost function C.
auto C = [&](int i, int j) {};

forn(i, n) {
    opt[i][i] = i;
    // Initialize dp[i][i] according to the problem
}

for (int i = N-2; i >= 0; i--) {
    forsn(j, i + 1, n) {
        int mn = INT_MAX;
        int cost = C(i, j);
        for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
            if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                opt[i][j] = k; 
                mn = dp[i][k] + dp[k+1][j] + cost; 
            }
        }
        dp[i][j] = mn; 
    }
}