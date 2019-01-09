#include <bits/stdc++.h>

using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> vvi;

vvi matmult(vvi A, vvi B) {
	if (A.front().size() != B.size()) return vvi();
	vvi result(A.size(), vi(B.front().size(), 1e9+1));
	for (int r = 0; r < result.size(); ++r) {
		for (int c = 0; c < result.front().size(); ++c) {
			for (int i = 0; i < A.front().size(); ++i) {
				result[r][c] = min(result[r][c], A[r][i] + B[i][c]);
			}
		}
	}
	return result;
}

int main() {
	int64_t n, m;
	cin >> n >> m;
	vvi mat(n, vi(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> mat[i][j];
		}
	}

	int64_t mn = 1e9+10;
	for (int i = 0; i < n; ++i) mn = min(mn, mat[0][i]);
	if (mn > m) {
		cout << 0 << endl;
		return 0;
	}

	vector<vvi> p2mats = {{}, mat};
	auto curr = matmult(mat, mat);
	for (int64_t p = 2; p <= m; p *= 2) {
		p2mats.push_back(curr);
		curr = matmult(curr, curr);
	}

	curr = mat;
	int64_t ans = 1;
	for (int64_t p = p2mats.size()-1; p > 0; --p) {
		auto ma = matmult(curr, p2mats[p]);
		int64_t mn = 1e9+10;
		for (int i = 0; i < n; ++i) mn = min(mn, ma[0][i]);
		if (mn <= m) {
			curr = ma;
			ans += 1ll<<(p-1);
		}
	}
	cout << ans << endl;
}
