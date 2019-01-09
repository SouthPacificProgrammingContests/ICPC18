#include <bits/stdc++.h>

using namespace std;

int main() {
	long long n, L, sum = 0;
	cin >> n >> L;
	string str;
	for (int i = 0; i < n; ++i) {
		cin >> str;
		sum += str.size();
	}


	// Best mod ever.
	for (int i = 1; i <= L; ++i) {
		if (sum + (n-1)*i == L) {
			cout << "Yes" << endl;
			return 0;
		}
	}

	cout << "No" << endl;
}