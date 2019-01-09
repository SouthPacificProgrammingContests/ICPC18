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

vvi matpower(vvi A, int64_t pow) {
	if (A.size() != A.front().size()) return vvi();
	vvi result = A;
	while (pow) {
		if (pow & 1) {
			result = matmult(result, A);
		}
		pow >>= 1;
		A = matmult(A, A);
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

	int lo = 0, hi = m, ans = -1;
	while (lo <= hi) {
		int mid = (lo+hi)/2;
		auto ma = matpower(mat, mid);
		int64_t mn = 1e9+10;
		for (int i = 0; i < n; ++i) mn = min(mn, ma[0][i]);
		if (mn > m) {
			hi = mid-1;
		} else {
			ans = max(ans, mid);
			lo = mid+1;
		}
	}
	cout << ans+1 << endl;
}