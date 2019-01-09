#include <bits/stdc++.h>
using namespace std;

vector<long long> factorial;

long long f(vector<int>& cnt,int idx,int available,int n,int m){
	if(idx == n){
		if(available != 0)
			return 0;

		vector<int> arr;
		for(int i=0;i<n;i++)
			for(int j=0;j<cnt[i];j++)
				arr.push_back(i);

		// Do they have the same modular distribution?
		vector<int> mods_cnt(min(n+1,m),0), mods_arr(min(n+1,m),0);
		for(int i=0;i<n;i++){
			mods_cnt[ cnt[i] % m ]++;
			mods_arr[ arr[i] % m ]++;
		}

		if(mods_arr != mods_cnt)
			return 0;
		
		long long ans = 1;
		for(int i=0;i<(int)mods_cnt.size();i++)
			ans *= factorial[mods_cnt[i]];

		for(int i=0;i<n;i++)
			ans /= factorial[cnt[i]];

		return ans;
	}

	long long ans = 0;
	for(int i=0;i<=available;i++){
		cnt[idx] = i;
		ans += f(cnt,idx+1,available-i,n,m);
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;

	factorial.resize(n+2);
	factorial[0] = 1;
	for(int i=1;i<n+2;i++)
		factorial[i] = factorial[i-1] * i;

	vector<int> cnt(n);

	cout << f(cnt,0,n,n,m) << endl;
}
