#include <bits/stdc++.h>
using namespace std;

int main(){
	string s;
	cin >> s;

	reverse(s.begin(), s.end());

	int n = s.length();

	string ans = "";
	for(int i=0,j=0;i<n;i=j){
		for(j=i;j<n && s[i] == s[j];j++);
		
		ans += string(4-(j-i)%4,s[i]);
	}

	cout << ans << endl;
}
