#include <bits/stdc++.h>

using namespace std;

const int LCM = 2520, MAXCOINS = 100, MAXAMT = 100;
int C[MAXCOINS], NC, DP[LCM*MAXAMT+1];

int f(int num) {
	if (num == 0) return 0;
	if (DP[num] != -1) return DP[num];
	int ans = 1e9;
	for (int i = 0; i < NC; ++i) if (num-C[i] >= 0)
		ans = min(ans, f(num-C[i])+1);
	return DP[num] = ans;
}

int main() {
	int amt;
	cin >> amt >> NC;
	for (int i = 0; i < NC; ++i) {
		int n, d;
		cin >> n >> d;
		C[i] = n*(LCM/d);
	}
	fill(DP, DP+LCM*amt+1, -1);
	int ans = f(amt*LCM);
	if (ans == 1e9) ans = -1;
	cout << ans << endl;
}
