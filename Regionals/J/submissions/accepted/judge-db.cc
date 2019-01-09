#include <bits/stdc++.h>
using namespace std;

const vector<string> D = {"Western", "Central", "Eastern"};

struct Team{
	string name, uni, div;
};

istream& operator>>(istream& is, Team& T) {
	is >> T.name >> T.div >> T.uni;
}

int main(){
	int n; cin >> n;
	vector<Team> A(n);

	for(int i=0;i<n;i++)
		cin >> A[i];

	vector<bool> selected(n);
	map<string, int> M;

	// Selection Step 1
	for(string div : D){
		string uni;
		for(int i=0;i<n;i++)
			if(A[i].div == div && A[i].uni != uni){
				selected[i] = true;
				M[A[i].uni]++;
				if(uni != "") break;
				uni = A[i].uni;
			}
		}

	// Selection Step 2
	for(int k=0;k<6;k++)
		for(int i=0;i<n;i++){
			if(selected[i]) continue;
			if(M[A[i].uni] == 2) continue;
			selected[i] = true;
			M[A[i].uni]++;
			break;
		}

	for(int i=0;i<n;i++)
		if(selected[i])
			cout << A[i].name << endl;
		else if(i < 12) cerr << i << endl;
}
