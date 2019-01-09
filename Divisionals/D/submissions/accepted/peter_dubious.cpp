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

ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll sum=0,N,d=0;
	cin >> N;
	for (int i=0;i<N;++i) {
		ll a;
		cin >> a;
		sum+=a*(i+1)*(N-i);
		//d+=(ll)(i+1)*(N-i);
	}
	d=(N+1)*(N)/2;
	ll g=gcd(sum,d);
	cout << sum/g << '/' << d/g << '\n';
}
