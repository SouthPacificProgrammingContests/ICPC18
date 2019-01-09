#include <bits/stdc++.h>

using namespace std;

int N, M, S, T;
vector<vector<tuple<int, int, int>>> adj;

int dijk1(int s, int e) {
	vector<int> D(N, (int)1e9+5);
	D[s] = 0;
	set<pair<int, int>> Q;
	Q.emplace(0, s);
	while (Q.size()) {
		int h, at;
		tie(h, at) = *Q.begin();
		Q.erase(Q.begin());
		if (at == e)
			return D[at];
		if (D[at] < h) continue;
		for (auto &e : adj[at]) {
			int h, l, n;
			tie(h,l,n) = e;
			if (D[n] <= max(h,D[at])) continue;
			D[n] = max(h,D[at]);
			Q.emplace(max(h,D[at]), n);
		}
	}
	return -1;
}

int64_t dijk2(int s, int e, int t) {
	vector<int64_t> D(N, 1e18);
	D[s] = 0;
	set<pair<int64_t, int>> Q;
	Q.emplace(0, s);
	while (Q.size()) {
		int64_t l, at;
		tie(l, at) = *Q.begin();
		Q.erase(Q.begin());
		if (at == e)
			return D[at];
		if (D[at] < l) continue;
		for (auto &e : adj[at]) {
			int64_t h, l, n;
			tie(h,l,n) = e;
			if (h>t || D[n]<=D[at]+l) continue;
			D[n] = D[at]+l;
			Q.emplace(D[at]+l, n);
		}
	}
	return -1;
}

int main() {
	cin >> N >> M >> S >> T;
	--S;--T;
	adj.resize(N);
	for (int i = 0; i < M; ++i) {
		int a,b,h,l;
		cin>>a>>b>>h>>l;
		--a;--b;
		adj[a].emplace_back(h,l,b);
		adj[b].emplace_back(h,l,a);
	}
	int t = dijk1(S,T);
	cout << t << endl << dijk2(S,T,t) << endl;
}
