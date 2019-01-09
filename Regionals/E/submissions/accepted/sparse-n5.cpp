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
	if (hypot(e.x,e.y) < hypot(f.x,f.y)) return 1;
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
vector<vector<int>> cross;

map<int, int> dp[155][155][305];

// int states = 0, work1 = 0, work2 = 0;

int f(int l, int r, int l1, int l2) {
	if (dp[l1][l2][l].count(r)) return dp[l1][l2][l][r];
	int ans = 0;
	for (int i = l; i <= r; ++i) {
		int ln1 = Ln[i];
		// ++work1;
		if (R[ln1] == i || cross[ln1][l1] || cross[ln1][l2] || R[ln1] > r) continue;
		for (int j = i+1; j <= r; ++j) {
			// ++work2;
			int ln2 = Ln[j];
			if (R[ln2] == j || cross[ln2][l1] || cross[ln2][l2] || R[ln2] > r || !cross[ln2][ln1]) continue;
			int tot = W[ln1]+W[ln2]+f(i+1, j-1, ln1, ln2);
			if (R[ln2] > R[ln1])
				tot += f(j+1, R[ln1]-1, ln1, ln2)+f(R[ln1]+1, R[ln2]-1, ln1, ln2)+f(R[ln2]+1, r, l1, l2);
			else
				tot += f(j+1, R[ln2]-1, ln1, ln2)+f(R[ln2]+1, R[ln1]-1, ln1, ln2)+f(R[ln1]+1, r, l1, l2);
			ans = max(ans, tot);
		}
	}
	// ++states;
	return dp[l1][l2][l][r] = ans;
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
	Ln = L = R = vector<int>(xs.size());
	auto done = L;
	for (int i = 0; i < xs.size(); ++i) {
		if (!done[xs[i].second]) {
			L[xs[i].second] = i;
			done[xs[i].second] = 1;
		} else
			R[xs[i].second] = i;
		Ln[i] = xs[i].second;
	}
	cross.assign(N+1, vector<int>(N+1));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < lines[i].size()-1; ++k)
				for (int l = 0; l < lines[j].size()-1; ++l) {
					Seg s{lines[i][k],lines[i][k+1]}, s2{lines[j][l],lines[j][l+1]};
					if (s.inter(s2)) cross[i][j] = 1;
				}
	cout << f(0, xs.size()-1, N, N) << endl;
	// cout << states << " " << work1 << " " << work2 << endl;
}
