#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	int last = 0, tmp, ans = 0;
	for (int i = 0; i < m; ++i) {
		cin >> tmp;
		if (tmp < last) ++ans;
		last = tmp;
	}
	cout << ans << endl;
}
