int ft[MAXN+1]; 
void upd(int i0, int v){
	for(int i=i0+1;i<=MAXN;i+=i&-i)ft[i]+=v;
}
int get(int i0){
	int r=0;
	for(int i=i0;i;i-=i&-i)r+=ft[i];
	return r;
}
int get_sum(int i0, int i1){ 
	return get(i1)-get(i0);
}