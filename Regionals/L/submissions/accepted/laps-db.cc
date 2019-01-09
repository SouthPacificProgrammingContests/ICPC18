#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, m; cin >> n >> m;
	vector<int> A(m);
	for(int i=0;i<m;i++) cin >> A[i];

	int ctr = 0;
	for(int i=1;i<m;i++)
		if(A[i] < A[i-1])
			ctr++;
	cout << ctr << endl;
}