// AC solution.
#include <bits/stdc++.h>

using namespace std;
#define X first
#define Y second
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define debug(x) cerr << #x << " = " << (x) << endl;
template<typename T>
ostream& operator<<(ostream& o, vector<T>& v) {
  for (auto& x : v) o << x << ' ';
  return o;
}

int main(){
  std::ios_base::sync_with_stdio(false); cin.tie(0);

  int P; cin >> P;
  int Ma = 1000000000, cap;
  string ans;
  for (int i = 0; i < P; i++) {
    string prob;
    int a, b, c;
    cin >> prob >> a >> b >> c;
    int sum = a + b + c;
    if (sum < Ma
        || (sum == Ma && a < cap)) {
      Ma = sum;
      cap = a;
      ans = prob;
    }
  }
  cout << ans << endl;
}
