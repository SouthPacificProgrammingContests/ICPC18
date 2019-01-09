#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> A(N);
	for (int &e : A) cin >> e;
	int l = A[0], r = 0, last = A[0];
	bool g = 1;
	for (int i = 1; i < N; ++i) {
		if (A[i] < last) {
			l -= (last-A[i]);
			if (l < 0) {
				g = 0;
				break;
			}
		} else if (A[i] > last) {
			r += (A[i]-last);
		}
		last = A[i];
	}
	cout << (g?"YES":"NO") << endl;
}