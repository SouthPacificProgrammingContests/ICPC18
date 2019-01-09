#include <bits/stdc++.h>

#define x first
#define y second

#ifdef ONLINE_JUDGE
#define DEBUG(x)
#else
#define DEBUG(x) cerr << #x << ": " << x << endl;
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;

const int mod=1000000000+7;

int addm(int& a,int b) {return (a+=b)<mod?a:a-=mod;}

template<class T,class U> bool smin(T& a,U b) {return a>b?(a=b,1):0;}
template<class T,class U> bool smax(T& a,U b) {return a<b?(a=b,1):0;}

bool possible[6];
int p[]{0,1,2};
int n;
char c;
int dates[100][3];
string strs[]{"YY","MM","DD"};

int daysinmonth(int year, int month) {
	if (month==2) return 28 + (year%4==0);
	if (month<=7) return month%2+30;
	return (month+1)%2+30;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i=0;i<n;++i) {
		cin >> dates[i][0] >> c >> dates[i][1] >> c >> dates[i][2];
	}

	for (int i=0;i<6;++i,next_permutation(p,p+3)) {
		possible[i] = 1;
		for (int j=0;j<n;++j) {
			if (dates[j][p[1]] == 0 || dates[j][p[1]] > 12
					|| dates[j][p[2]] == 0 || dates[j][p[2]] >
					daysinmonth(dates[j][p[0]]+2000, dates[j][p[1]]))
				possible[i]=0;
		}
	}

	int nvalid = accumulate(possible,possible+6,0);
	if (nvalid==0) cout << "IMPOSSIBLE\n";
	else if (nvalid>1) cout << "UNSURE\n";
	else {
		iota(p,p+3,0);
		for (int i=0;!possible[i];++i,next_permutation(p,p+3));
		for (int i=0;i<3;++i) for (int j=0;j<3;++j)
			if (p[j]==i) {
				cout << strs[j];
				if (i<2) cout << "/";
			}
		cout << "\n";
	}
}
