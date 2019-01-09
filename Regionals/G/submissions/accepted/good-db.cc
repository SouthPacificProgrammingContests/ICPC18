#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, Q; cin >> n >> Q;
	n++;

	int logg = 1; while((1 << logg) <= 2*n) logg++;
	
	vector<char> upgrades(n, 'L'); // upgrades[0] == 'L'
	vector<int> depth(n);
	vector<vector<int> > par(logg, vector<int>(n, 0));

	for(int i=1;i<n;i++){
		cin >> upgrades[i] >> par[0][i]; par[0][i]--;
		depth[i] = depth[par[0][i]]+1;
	}
	
	for(int i=1;i<logg;i++)
		for(int v=0;v<n;v++)
			par[i][v] = par[i-1][ par[i-1][v] ];

	int ans = 0;
	while(Q--){
		int u, v; cin >> u >> v; u--; v--;
		if(depth[u] > depth[v]) swap(u, v);
		for(int i=logg-1;i>=0;i--)
			if(depth[v] - (1 << i) > depth[u])
				v = par[i][v];

		int care_about = v;

		if(par[0][v] != u){
			if(depth[v] != depth[u]) v = par[0][v];
			for(int i=logg-1;i>=0;i--)
				if(par[i][u] != par[i][v])
					u = par[i][u], v = par[i][v];
			care_about = min(u, v);
		}
		ans += (upgrades[care_about] == 'L');
	}
	cout << ans << endl;
}
