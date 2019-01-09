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

const ld PI = acos(-1.0);

bool insq(ld side_len, ld x, ld y) {
	return x >= 0 && y >= 0 && x <= side_len && y <= side_len;
}

int main() {
	V<ld> sides(3);
	READALL(sides);
	sort(ALL(sides));

	ld ans = 1e9;

	do {

		ld a = sides[0], b = sides[1], c = sides[2];

		ld a1 = acos((a*a+c*c-b*b)/(2*a*c));

		ld lo = 0, hi = 1e12;

		FO(it, 150) {
			ld side_len = (lo+hi)/2;
			ld lo2 = 0, hi2 = PI/2, best = 11;
			FO(it2, 150) {
				ld a2 = (lo2+hi2)/2;
				ld x = cos(a2)*a, y = sin(a2)*a;
				if (!insq(side_len,x,y)) {
					lo2 = a2;
				} else {
					best = min(best, a2);
					hi2 = a2;
				}
			}
			ld x = cos(a1+best)*c, y = sin(a1+best)*c;
			if (best>10 || !insq(side_len,x,y)) {
				lo = side_len;
			} else {
				hi = side_len;
			}
		}
		ans = min(ans, lo);
	} while (next_permutation(ALL(sides)));

	cout << fixed << setprecision(20) << ans << endl;


}
