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

bool reachable(int src, int dest, int haz_lvl, vector<bool>& vis){
	if(src == dest) return true;
	if(vis[src]) return false;
	vis[src] = true;
	for(const auto& edge : adj[src]){
		int u, H; tie(u, H, std::ignore) = edge;
		if(H <= haz_lvl && reachable(u, dest, haz_lvl, vis))
			return true;
	}
	return false;
}

bool can(int src, int dest, int haz_lvl){
	vector<bool> vis(adj.size(), false);
	return reachable(src, dest, haz_lvl, vis);
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
	while(!can(s, t, hi)) hi *= 2;
	while(hi - lo > 4){
		int mid = (lo + hi) / 2;
		(!can(s, t, mid) ? lo : hi) = mid;
	}
	while(!can(s, t, lo)) lo++;
	cout << lo << endl << dist(s,t,lo) << endl;
}
