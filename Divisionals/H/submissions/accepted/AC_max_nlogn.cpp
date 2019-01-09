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


int main() {
	int N;
	cin >> N;
	V<int> A(N);
	READALL(A);

	int distinct = set<int>(ALL(A)).size();

	int r = 0, ans = 0;
	map<int, int> cnts;
	FO(l, N) {
		while (cnts.size() < distinct && r < N) {
			cnts[A[r]]++;
			++r;
		}
		if (cnts.size() < distinct) {
			ans = max(ans, N-l+1);
			break;
		}
		ans = max(ans, r-l);
		cnts[A[l]]--;
		if (cnts[A[l]] == 0) cnts.erase(A[l]);
	}

	cout << ans << endl;
}
