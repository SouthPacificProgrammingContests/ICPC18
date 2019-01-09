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

int ceil_pow_2(int v) {
	int p; for (p = 1; p < v; p *= 2) {} return p;
}

struct Stree {
	int N;
	V<int> node_vals;
	void init(int sz) {
		N = ceil_pow_2(sz);
		node_vals.resize(2*N-1);
	}
	void update(int l, int r, int nid, int nl, int nr) {
		if (l == nl && r == nr) {
			node_vals[nid] = 1;
			return;
		}
		int mid = (nl+nr)/2;
		if (l <= mid)
			update(l, min(r, mid), 2*nid+1, nl, mid);
		if (r > mid)
			update(max(l, mid+1), r, 2*nid+2, mid+1, nr);
	}
	void update(int l, int r) {
		update(l, r, 0, 0, N-1);
	}
	bool query(int idx, int nid, int nl, int nr) {
		if (node_vals[nid])
			return 1;
		if (nl == nr)
			return 0;
		int mid = (nl+nr)/2;
		if (idx <= mid && query(idx, 2*nid+1, nl, mid))
			return 1;
		else if (idx > mid && query(idx, 2*nid+2, mid+1, nr))
			return 1;
		return 0;
	}
	bool query(int idx) {
		return query(idx, 0, 0, N-1);
	}
};

struct Stree2D {
	int N;
	V<Stree> node_vals;
	void init(int sz, int sz2) {
		N = ceil_pow_2(sz);
		node_vals.resize(2*N-1);
		FO(i, node_vals.size()) node_vals[i].init(sz2);
	}
	int ll, rr;
	void update(int l, int r, int nid, int nl, int nr) {
		if (l == nl && r == nr) {
			node_vals[nid].update(ll, rr);
			return;
		}
		int mid = (nl+nr)/2;
		if (l <= mid)
			update(l, min(r, mid), 2*nid+1, nl, mid);
		if (r > mid)
			update(max(l, mid+1), r, 2*nid+2, mid+1, nr);
	}
	void update(int l, int r, int ll, int rr) {
		this->ll = ll;
		this->rr = rr;
		update(l, r, 0, 0, N-1);
	}
	int idx2;
	bool query(int idx, int nid, int nl, int nr) {
		if (node_vals[nid].query(idx2))
			return 1;
		if (nl == nr)
			return 0;
		int mid = (nl+nr)/2;
		if (idx <= mid && query(idx, 2*nid+1, nl, mid))
			return 1;
		else if (idx > mid && query(idx, 2*nid+2, mid+1, nr))
			return 1;
		return 0;
	}
	bool query(int idx, int idx2) {
		this->idx2 = idx2;
		return query(idx, 0, 0, N-1);
	}
};



int main() {
	int R, C, K;
	cin >> R >> C >> K;
	Stree2D st;
	st.init(R, C);
	int sr, sc;
	FO(r, R) FO(c, C) {
		char gc;
		cin >> gc;
		if (gc == 'X') st.update(r, r, c, c);
		if (gc == 'S') {
			sr = r;
			sc = c;
		}
	}
	queue<pair<int, int>> Q, nextQ;
	Q.emplace(sr, sc);
	V<V<int>> D(R, V<int>(C));
	D[sr][sc] = 1;
	V<V<int>> dirs = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
	int ansr, ansc;
	FO(k, K) {
		int r1,c1,r2,c2;
		cin >> r1 >> c1 >> r2 >> c2;
		--r1; --r2; --c1; --c2;
		nextQ = {};
		while (Q.size()) {
			int r, c;
			tie(r,c) = Q.front();
			Q.pop();
			if (st.query(r,c)) continue;
			for (auto &dir : dirs) {
				int rr = r+dir[0], cc = c+dir[1];
				if (rr < 0 || rr >= R || cc < 0 || cc >= C) continue;
				if (D[rr][cc] || st.query(rr,cc)) continue;
				D[rr][cc] = 1;
				nextQ.emplace(rr, cc);
			}
		}
		st.update(r1, r2, c1, c2);
		Q = nextQ;
	}
	FO(r, R) FO(c, C) if (D[r][c] && !st.query(r, c)) {
		cout << r+1 << " " << c+1 << endl;
		return 0;
	}
	cout << -1 << endl;
}
