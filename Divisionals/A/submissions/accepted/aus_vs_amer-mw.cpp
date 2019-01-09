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

bool valid_month(int m) {
	return m >= 1 && m <= 12;
}

V<int> days = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool valid_day(int d, int m, int y) {
	if (y%4 == 0 && m == 2) {
		return d >= 1 && d <= 29;
	}
	return d >= 1 && d <= days[m];
}

int main() {

	int N;
	cin >> N;

	V<V<int>> dates(N);

	FO(i, N) {
		int a,b,c;
		char tmp;
		cin >> a >> tmp >> b >> tmp >> c;
		dates[i] = {a,b,c};
	}

	V<int> perm = {0,1,2};

	int num_ans = 0;
	V<int> ans_perm;

	do {
		bool g = 1;
		FO(i, N) {
			int d = dates[i][perm[0]], m = dates[i][perm[1]], y = dates[i][perm[2]];
			if (!valid_month(m)) {
				g = 0;
				break;
			}
			if (!valid_day(d,m,y)) {
				g = 0;
				break;
			}
			
		}
		if (g) {
			++num_ans;
			ans_perm = perm;
		}
	} while (next_permutation(ALL(perm)));

	if (num_ans == 0) {
		cout << "IMPOSSIBLE" << endl;
	} else if (num_ans > 1) {
		cout << "UNSURE" << endl;
	} else {
		V<string> parts = {"DD","MM","YY"};
		V<int> iperm(3);
		FO(i, 3) iperm[ans_perm[i]] = i;
		cout << parts[iperm[0]] << "/" << parts[iperm[1]] << "/" << parts[iperm[2]] << endl;
	}
}
