#include <bits/stdc++.h>
using namespace std;

int main(){
	int n; cin >> n;
	vector<int> A(n);
	for(auto& x : A) cin >> x;
    A.push_back(0); // Life hack!

	int forced_right = 0;
	string ans = "YES";
	for(int i=0;i<n;i++){
	    if(A[i] < forced_right) ans = "NO";
	    forced_right += max(A[i+1] - A[i], 0);
	}
	cout << ans << endl;
}
