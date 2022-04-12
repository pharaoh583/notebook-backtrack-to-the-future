//all for dkp :') and to reach the world finals
//solution for problem uva 10330 
#include <bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < int(n); i++)
#define forsn(i,s,n) for(int i = int(s); i < int(n); i++)
#define forit(i, str) for(auto i = str.begin(); i != str.end(); i++)
#define DBG(x) cerr << #x << " = " << (x) << endl
#define all(v) (v).begin(),(v).end()
#define FastIO ios_base::sync_with_stdio(false); cin.tie(NULL)
#define ll long long 
#define ii pair<int,int>
#define vi vector<int>
#define F first
#define S second
#define pb push_back
#define pf push_front
#define mp make_pair
#define INF 1000000000
using namespace std;
int MAX_V = 202;
int mf, f, s = 0, t = 201;
map<int, int> res[202];
int dat[100];
vi p;

void augment(int v, int minEdge){
	if(v == s){
		f = minEdge; return;
	}
	else if(p[v] != -1){
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f; res[v][p[v]] += f;
	}
}

void init(){
	forn(i, MAX_V) res[i].clear();
}

int main(){
	FastIO;
	int n; 
	while(cin>>n){
		init();
		int cont = 0;
		forn(i, n){
			int cap; cin>>cap;
			dat[i] = 2 * (cont ++) + 1;
			res[dat[i]][dat[i] + 1] = cap;
			res[dat[i] + 1][dat[i]] = 0;
		}
		int m; cin>>m;
		forn(i, m){
			int a, b, c; cin>>a>>b>>c,a--,b--;
			res[dat[a] + 1][dat[b]] = c;
			res[dat[b]][dat[a] + 1] = 0;	
		}
		int b, d; cin>>b>>d;
		forn(i, b){
			int a; cin>>a, a--;
			res[s][dat[a]] = INF;
			res[dat[a]][s] = 0;
		}
		forn(i, d){
			int a; cin>>a, a--;
			res[dat[a] + 1][t] = INF;
			res[t][dat[a] + 1] = 0;
		}
//		forn(i, 2 * n + 1){
//			cout<<"for node: "<<i<<endl;
//			forit(it, res[i]){
//				cout<<"\t"<<(*it).F<<" "<<(*it).S<<endl;
//			}
//		}
//		cout<<endl;
		mf = 0;
		while(true){
			f = 0;
			vi dist(MAX_V, INF); dist[s] = 0; queue<int> q; q.push(s);
			p.assign(MAX_V, -1);
			while(!q.empty()){
				int u = q.front(); q.pop();
//				cout<<"visiting: "<<u<<endl;
				if(u == t) break;
				forit(i, res[u]){
					int v = (*i).F;
					int cap = (*i).S;
					if(cap > 0 and dist[v] == INF)
						dist[v] = dist[u] + 1, q.push(v), p[v] = u;
				}
			}
//			forn(i, 2 * n + 1) cout<<p[i]<<" ";
//			cout<<p[t]<<endl;
			augment(t, INF);
//			cout<<f<<endl;
			if(f == 0) break;
			mf += f;
		}
		cout<<mf<<endl;
	}
}



