#include <bits/stdc++.h>

using namespace std;


int main() {
	int64_t N;
	cin >> N;
	vector<int64_t> A(N);
	for (auto &e : A) cin >> e;
	int64_t sum = 0;
	for (int i = 0; i < N; ++i) sum += A[i]*(i+1)*(N-i);
	int64_t g = __gcd(sum, N*(N+1)/2);
	cout << sum/g << "/" << (N*(N+1)/2)/g << endl;
}
