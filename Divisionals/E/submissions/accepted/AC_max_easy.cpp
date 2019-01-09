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

// floats should work, but I would to check

int main() {
	int P;
	cin >> P;
	string name, ans;
	int a, b, c;
	int bestsum = 1e9, besta;
	FO(i, P) {
		cin >> name >> a >> b >> c;
		if (a+b+c < bestsum) {
			bestsum = a+b+c;
			ans = name;
			besta = a;
		} else if (a+b+c == bestsum && a < besta) {
			bestsum = a+b+c;
			ans = name;
			besta = a;
		}
	}
	cout << ans << endl;
}
