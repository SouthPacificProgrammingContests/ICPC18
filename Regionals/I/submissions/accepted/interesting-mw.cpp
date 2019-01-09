#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> C, Amf, Cmf;
vector<int64_t> fact;

int64_t f(int i, int rem) {
	int64_t ans = 0;
	if (i == n) {
		if (rem) return 0;
		ans = 1;
		Amf = Cmf = vector<int>(n+1, 0);
		for (int i = 0; i < n; ++i) {
			Cmf[C[i]%m]++;
			Amf[i%m] += C[i];
		}
		if (Cmf != Amf) return 0;
		for (int i = 0; i <= n; ++i) ans *= fact[Cmf[i]];
		for (int i = 0; i < n; ++i) ans /= fact[C[i]];
		return ans;
	}
	for (int v = 0; v <= rem; ++v) {
		C[i] = v;
		ans += f(i+1, rem-v);
	}
	return ans;
}


int main() {
	cin >> n >> m;
	fact.resize(n+1);
	fact[0] = 1;
	for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
	C.resize(n);
	cout << f(0, n) << endl;
}
