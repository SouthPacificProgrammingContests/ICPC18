#include <bits/stdc++.h>

using namespace std;

template <typename T>
using V = vector<T>;

typedef long double ld;
typedef long long ll;

#define FO(i, N) for (int (i) = 0; (i) < (N); ++(i))
#define FOll(i, N) for (ll (i) = 0; (i) < (N); ++(i))
#define READALL(c) for (auto &e : c) { cin >> e; }
#define PRINTALL(c) for (const auto &e : c) { cout << e << "\t"; } cout << "\n";
#define MP(x, y) (make_pair((x), (y)))
#define MT(...) make_tuple(__VA_ARGS__)
#define G(i, x) get<i>(x)
#define ALL(x) begin(x), end(x)

int N;
set<int> adj[5000];

void dfs(int at, V<int> &vis, bool any) {
	vis[at] = 1;
	FO(i, N) if (!vis[i]) {
		if (adj[at].count(i) || (any && adj[i].count(at))) {
			dfs(i, vis, any);
		}
	}
}


int main() {
	int X, Y, u, v;
	cin >> N >> X >> Y;

	FO(x, X) {
		cin >> u >> v;
		--u;--v;
		adj[u].insert(v);
		adj[v].insert(u);
	}

	FO(y, Y) {
		cin >> u >> v;
		--u;--v;
		adj[u].insert(v);
	}

	V<int> vis1(N), vis2(N);
	dfs(0, vis1, 0);
	dfs(0, vis2, 1);

	FO(i, N) {
		if (!vis2[i]) {
			cout << "Impossible" << endl;
		} else if (!vis1[i]) {
			cout << "Ticket" << endl;
		} else {
			cout << "No Ticket" << endl;
		}
	}
}
