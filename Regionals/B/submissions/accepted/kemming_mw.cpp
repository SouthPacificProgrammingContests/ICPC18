#include <bits/stdc++.h>

using namespace std;


vector<int> zalgorithm(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R-L] == s[R]) R++;
            z[i] = R-L; R--;
        } else {
            int k = i-L;
            if (z[k] < R-i+1) z[i] = z[k];
            else {
                L = i;
                while (R < n && s[R-L] == s[R]) R++;
                z[i] = R-L; R--;
            }
        }
    }
    z[0] = n;
    return z;
}

int ans(string a, string b) {
	auto z = zalgorithm(a+"$"+b);
	return *max_element(begin(z)+a.size()+1, end(z));
}

int main() {
	string S, odd, eve;
	cin >> S;

	int N = S.size();

	for (int i = 0; i < N; ++i) {
		if (i%2)
			odd.push_back(S[i]);
		else
			eve.push_back(S[i]);
	}

	cout << min(N, max(ans(odd, S)*2+1, ans(eve, S)*2)) << endl;
}
