#include <bits/stdc++.h>
using namespace std;

// ----------------------------------------------------------------------------
//                             Debugging template
// ----------------------------------------------------------------------------

namespace {
#pragma GCC diagnostic ignored "-Wunused-function"

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define len(x) (int)((x).size())
#define X first
#define Y second

#define FOR(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

// Types
using ll = long long int;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vll = vector<ll>;
template<typename T> using minpq = priority_queue<T, vector<T>, greater<T>>;

#ifndef ONLINE_JUDGE
#define DEBUG(args...) cerr << "[Line " << __LINE__ << "]: ";  { vector<string> _v = __split(#args, ','); __ferr(_v.begin(), args); }
#define DEBUG_2D(A) cerr << "[Line " << __LINE__ << "]: " << #A << " = \n";  for (const auto& R : (A)) { cerr << '\t' << R << '\n'; }
vector<string> __split(const string& s, char c) { vector<string> v; stringstream ss(s); string x; while (getline(ss, x, c)) v.emplace_back(x);  return v; }
void __err(vector<string>::iterator it) { cerr << endl; }
template<typename T, typename... Args> void __err(vector<string>::iterator it, T a, Args... args) { cerr << ", " << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a; __err(++it, args...); }
template<typename T, typename... Args> void __ferr(vector<string>::iterator it, T a, Args... args) { cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a; __err(++it, args...); }
#else
#define DEBUG(...) 
#define DEBUG_2D(...)
#endif  // ONLINE_JUDGE

// Printing containers
template<typename U, typename V> ostream& operator<<(ostream &s, const pair<U, V> &x) { s << "(" << x.first << ", " << x.second << ")"; return s; }
template<typename U> ostream& operator<<(ostream &s, const vector<U> &x) { s << "["; bool was = false; for (auto it : x) { if (was) s << ", "; was = true; s << it; } s << "]";  return s; }
template<typename U> ostream& operator<<(ostream &s, const deque<U> &x) { s << "["; bool was = false; for (auto it : x) { if (was) s << ", "; was = true; s << it; } s << "]"; return s; }
template<typename U, typename V> ostream& operator<<(ostream &s, const map<U, V> &x) { s << "{"; bool was = false; for (auto it : x) { if (was) s << ", "; was = true; s << it; }  s << "}"; return s; }
template<typename U> ostream& operator<<(ostream &s, const set<U> &x) { s << "{"; bool was = false; for (auto it : x) { if (was) s << ", "; was = true; s << it; } s << "}"; return s; }
template<typename U> ostream& operator<<(ostream &s, const multiset<U> &x) { s << "{"; bool was = false; for (auto it : x) { if (was) s << ", "; was = true; s << it; } s << "}"; return s; }

// Useful functions
ll expmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
template<typename T> T sqr(const T& x) { return x*x; }
ll flog(const ll x) { return 63 - __builtin_clzll(x); }
template<typename T> void sort(T& t) { sort(all(t)); }
template<typename T> void undupe(vector<T>& v) { sort(v); v.erase(unique(all(v)), v.end()); }
template<typename T> string binary(T x, int w=8*sizeof(T)) { string r; for (int i=0;i<w;i++) r=(((T(1)<<i)&x)?'1':'0')+r; return r; }
}

// ----------------------------------------------------------------------------
//                             Code binder code
// ----------------------------------------------------------------------------

bool leap_year(int y) { return (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)); }
int days_in(int y, int m) { return m == 2 ? 28 + leap_year(y) : 31 - (m-1) % 7 % 2; }

// ----------------------------------------------------------------------------
//                             Solution starts here
// ----------------------------------------------------------------------------

bool valid(int dd, int mm, int yy) {
  if (mm < 1 || mm > 12) return false;
  if (dd < 1 || dd > days_in(2000 + yy, mm)) return false;
  return true;
}

const string format[] = {"DD", "MM", "YY"};

int main() {
  int n;
  cin >> n;
  
  vector<array<int,3>> dates(n);
  for (auto& date : dates) {
    scanf("%d/%d/%d", &date[0], &date[1], &date[2]);
  }

  vi p = {0,1,2};
  string answer = "";
  
  do {
    bool v = true;
    for (const auto& date : dates) {
      array<int,3> pdate;
      pdate[p[0]] = date[0], pdate[p[1]] = date[1], pdate[p[2]] = date[2];
      if (!valid(pdate[0], pdate[1], pdate[2])) v = false;
    }
    if (v && answer != "") {
      cout << "UNSURE\n";
      return 0;
    } else if (v) {
      answer = format[p[0]] + "/" + format[p[1]] + "/" + format[p[2]];
    }
  } while (next_permutation(all(p)));

  if (answer != "") cout << answer << '\n';
  else cout << "IMPOSSIBLE\n";
}


