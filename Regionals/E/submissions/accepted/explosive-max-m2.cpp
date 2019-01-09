#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Pt {
	ll x, y;
	Pt operator-(const Pt &o) const {
		return {x-o.x, y-o.y};
	}
};

int dir(Pt a, Pt b, Pt c) {
	auto e = b-a, f = c-a;
	ll d = e.x*f.y-f.x*e.y;
	if (d > 0) return 1;
	if (d < 0 || e.x*f.x < 0 || e.y*f.y < 0) return -1;
	if (e.x*e.x+e.y*e.y < f.x*f.x+f.y*f.y) return 1;
	return 0;
}

struct Seg {
	Pt s, e;
	bool inter(const Seg &o) {
		return dir(s,e,o.s)*dir(s,e,o.e) <= 0 && dir(o.s,o.e,s)*dir(o.s,o.e,e) <= 0;
	}
};

int N;
vector<vector<Pt>> lines;
vector<int> W, Ln, L, R;
vector<vector<int>> cross, adj;

int dp[155][155][305];


int f(int l1, int l2, int i) {
	if (dp[l1][l2][i] != -1) return dp[l1][l2][i];
	int ans = 0;
	if (i != L[l1] && i != R[l1] && i != L[l2] && i != R[l2]) {
		ans = max(ans, f(l1, l2, i+1));
		int ln1 = Ln[i];
		if (R[ln1] != i && !cross[ln1][l1] && !cross[ln1][l2]) {
			for (int ln2 : adj[ln1]) if (L[ln2] > i) {
				int j = L[ln2];
				if (cross[ln2][l1] || cross[ln2][l2]) continue;
				int tot = W[ln1]+W[ln2]+f(ln1, ln2, i+1);
				if (R[ln2] > R[ln1])
					tot += f(ln1, ln2, j+1)+f(ln1, ln2, R[ln1]+1)+f(l1, l2, R[ln2]+1);
				else
					tot += f(ln1, ln2, j+1)+f(ln1, ln2, R[ln2]+1)+f(l1, l2, R[ln1]+1);
				ans = max(ans, tot);
			}	
		}
	}
	return dp[l1][l2][i] = ans;
}

int main() {
	cin >> N;
	lines.resize(N);
	W.resize(N);
	vector<pair<int, int>> xs;
	for (int i = 0; i < N; ++i) {
		cin >> W[i];
		int cnt;
		cin >> cnt;
		lines[i].resize(cnt);
		for (int j = 0; j < cnt; ++j)
			cin >> lines[i][j].x >> lines[i][j].y;
		xs.emplace_back(lines[i].front().x, i);
		xs.emplace_back(lines[i].back().x, i);
	}
	sort(begin(xs), end(xs));
	Ln = vector<int>(xs.size());
	L = R = vector<int>(N+1);
	auto done = L;
	for (int i = 0; i < xs.size(); ++i) {
		if (!done[xs[i].second]) {
			L[xs[i].second] = i;
			done[xs[i].second] = 1;
		} else
			R[xs[i].second] = i;
		Ln[i] = xs[i].second;
	}
	L[N] = -1;
	R[N] = xs.size();
	cross.assign(N+1, vector<int>(N+1));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < lines[i].size()-1; ++k)
				for (int l = 0; l < lines[j].size()-1; ++l) {
					Seg s{lines[i][k],lines[i][k+1]}, s2{lines[j][l],lines[j][l+1]};
					if (s.inter(s2)) cross[i][j] = 1;
				}
	adj.resize(N+1);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) if (i != j && cross[i][j])
			adj[i].push_back(j);
	memset(dp, -1, sizeof dp);
	cout << f(N, N, 0) << endl;
}
