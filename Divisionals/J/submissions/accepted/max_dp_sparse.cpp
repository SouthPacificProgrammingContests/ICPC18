#include <bits/stdc++.h>

using namespace std;

struct rat {
	int64_t num, den;
	void simplify() {
		int64_t g = __gcd(num, den);
		num /= g;
		den /= g;
	}
	rat(int64_t n, int64_t d) : num(n), den(d) {
		simplify();
	}
	rat() : rat(0,1) {}
	rat operator-(const rat &rhs) const {
		return rat(num*rhs.den-rhs.num*den, den*rhs.den);
	}
	bool operator<(const rat &rhs) const {
		return num*rhs.den < rhs.num*den;
	}
};

const int MAXCOINS = 100;
map<rat, int> DP;
rat C[MAXCOINS];
int NC;

int f(rat n) {
	if (n.num == 0) return 0;
	int ans = 1e9;
	if (DP.count(n)) return DP[n];
	for (int i = 0; i < NC; ++i) if (!(n<C[i]))
		ans = min(ans, f(n-C[i])+1);
	return DP[n] = ans;
}

int main() {
	int amt;
	cin >> amt >> NC;
	for (int i = 0; i < NC; ++i) {
		int n,d;
		cin >> n >> d;
		C[i] = rat(n,d);
	}
	int ans = f(rat(amt, 1));
	if (ans == 1e9) ans = -1;
	cout << ans << endl;
}
