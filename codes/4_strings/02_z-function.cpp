vi z_function(string& s) {
    int l = 0, r = 0, n = s.size();
    vi z(n, 0); //z[i] = max k: s[0, k) == s[i, i + k)
    forsn(i, 1, n) {
        if(i <= r) z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}