#include <bits/stdc++.h>

using namespace std;

struct onion_find {
	vector<int> par, rank;
	onion_find(int n) {
		par.assign(n, -1);
		for (int i = 0; i < n; ++i) par[i] = i;
		rank.assign(n, 1);
	}
	int find(int a) {
		return par[a] == a ? a : par[a] = find(par[a]);
	}
	void onion(int a, int b) {
		int ra = find(a), rb = find(b);
		if (ra == rb) return;
		if (rank[ra] > rank[rb]) swap(ra, rb);
		par[ra] = rb;
		if (rank[ra] == rank[rb]) ++rank[rb];
	}
};

int main() {
	int N, F, Q;
	cin >> N >> F >> Q;
	set<pair<int, int>> E;
	vector<tuple<char, int, int>> queries; 
	for (int i = 0; i < F; ++i) {
		int a, b;
		cin >> a >> b;
		E.emplace(a-1, b-1);
	}
	for (int i = 0; i < Q; ++i) {
		char t;
		int a, b;
		cin >> t >> a >> b;
		--a; --b;
		if (t == 'E') E.erase(make_pair(a, b));
		queries.emplace_back(t, a, b);
	}
	onion_find of(N);
	for (auto &e : E) of.onion(e.first, e.second);
	vector<int> ans;
	for (int i = Q-1; i >= 0; --i) {
	    char t;
		int a, b;
		tie(t, a, b) = queries[i];
		if (t == 'E') of.onion(a, b);
		else ans.push_back(of.find(a)==of.find(b));
	}
	for (int i = (int)ans.size()-1; i >= 0; --i)
		cout << (ans[i]?"YES":"NO") << endl;
}
