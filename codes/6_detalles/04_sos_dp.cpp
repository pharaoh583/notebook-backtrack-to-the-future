//first init sum[i] = value[i]
for (int k = 0; k < maxn; k++) {
    for (int s = 0; s < (1<<maxn); s++) {
        if(s&(1<<k)) sum[s] += sum[s^(1<<k)];
    }
}   