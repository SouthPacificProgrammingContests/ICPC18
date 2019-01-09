#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;
	multiset<int> PQ;
	vector<vector<int>> stars(N+1);
	for (int i = 0; i < N; ++i) {
		int t, s;
		cin >> t >> s;
		if (s <= N) stars[s].push_back(t);
	}
	long long t = 0, cnt = 0;
	for (int t : stars[0]) PQ.insert(t);
	while (PQ.size() && cnt < K) {
		t += *PQ.begin();
		PQ.erase(PQ.begin());
		++cnt;
		for (int t : stars[cnt]) PQ.insert(t);
	}
	if (cnt != K) cout << "IMPOSSIBLE" << endl;
	else cout << t << endl;
}