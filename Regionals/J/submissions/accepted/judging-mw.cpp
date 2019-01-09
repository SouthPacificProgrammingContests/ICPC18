#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<string>> S(n, vector<string>(3));
	for (int i = 0; i < n; ++i) {
		cin >> S[i][0] >> S[i][1] >> S[i][2];
	}
	vector<bool> sel(n);
	map<string, int> divcnt;
	map<string, int> unicnt;
	int c = 0;
	for (int i = 0; i < n && c < 6; ++i) {
		if (divcnt[S[i][1]] < 2 && unicnt[S[i][2]] == 0) {
			sel[i] = true;
			divcnt[S[i][1]]++;
			unicnt[S[i][2]]++;
			++c;
		}
	}
	for (int i = 0; i < n && c < 12; ++i) {
		if (sel[i]) continue;
		if (unicnt[S[i][2]] == 2) continue;
		sel[i] = true;
		unicnt[S[i][2]]++;
		++c;
	}
	for (int i = 0; i < n; ++i) {
		if (sel[i]) {
			cout << S[i][0] << endl;
		}
	}
}