// This solution has an extra O(log n) factor.

#include <bits/stdc++.h>
using namespace std;

vector<vector<tuple<int,int,int> > > adj;

long long dist(int src, int dest, int haz_lvl){
	priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
	pq.emplace(0, src);
	vector<long long> dist(adj.size(), -1);
	while(!pq.empty()){
		long long d = pq.top().first; int v = pq.top().second;
		pq.pop();
		if(dist[v] != -1) continue;
		dist[v] = d;
		for(const auto& edge : adj[v]){
			int u, H, L; tie(u, H, L) = edge;
			if(H <= haz_lvl)
				pq.emplace(d + L, u);
		}
	}
	return dist[dest];
}

int main(){
	int n, m, s, t;
	cin >> n >> m >> s >> t; s--; t--;

	adj.resize(n);
	for(int i=0;i<m;i++){
		int u, v; cin >> u >> v; u--; v--;
		int H, L; cin >> H >> L;
		adj[u].emplace_back(v, H, L);
		adj[v].emplace_back(u, H, L);
	}
	int lo = 1, hi = 1;
	while(dist(s, t, hi) == -1) hi *= 2;
	while(hi - lo > 4){
		int mid = (lo + hi) / 2;
		(dist(s, t, mid) == -1 ? lo : hi) = mid;
	}
	while(dist(s, t, lo) == -1) lo++;
	cout << lo << endl << dist(s,t,lo) << endl;
}
