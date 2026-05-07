//This optimization is used when we have to partition
//an array into k subarrays. Each subarray have a cost
//First make sure the following
//C(a, c) + C(b, d) <= C(a, d) + C(b, c) //QI
//O(n^2m) -> O(nmlogn) assuming O(C(i, j)) = O(1)
int n, m; //amount of elements, amount of partitions
vector<ll> dp_before, dp_cur;
ll C(int i, int j) {} //TODO: implement cost function
void compute(int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l + r) >> 1;
    for(int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }
    dp_cur[mid] = best.first;
    int opt = best.second;
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
ll solveDp() {
    dp_before.assign(n, 0);
    dp_cur.assign(n, 0);
    forn(i, n) dp_before[i] = C(0, i);
    forsn(i, 1, m) {
        compute(0, n - 1, 0, n - 1);
        swap(dp_before, dp_cur);
    }
    return dp_before[n - 1];
}