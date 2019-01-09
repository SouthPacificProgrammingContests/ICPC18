#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iostream>
#include <cassert>
#include <queue>
#include <string>
#include <functional>

using namespace std;
#define DBG false

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

template<typename T> struct FenwickTree2D {
  int N, M; vector<vector<T>> A;
  FenwickTree2D(int n, int m): N(n), M(m), A(n + 1, vector<T>(m + 1, 0)) {}
  T query(int i, int j) {
    T sum = 0;
    int x = i;
    while (x > 0) {
      int y = j;
      while (y > 0) {
        sum += A[x][y];
        y -= (y & -y);
      }
      x -= (x & -x);
    }
    return sum;
  }
  
  void update(int i, int j, T v){
    int x = i;
    while (x <= N) {
      int y = j;
      while (y <= M) {
        A[x][y] += v;
        y += (y & -y);
      }
      x += (x & -x);
    }
  }

  T query(int i, int j, int i2, int j2) {
    return query(i, j) + query(i2 + 1, j2 + 1) - query(i, j2 + 1) - query(i2 + 1, j);
  }

  void update(int i, int j, int i2, int j2, T val) {
    update(i, j, val);
    update(i2 + 1, j, -val);
    update(i, j2 + 1, -val);
    update(i2 + 1, j2 + 1, val);
  }
};

void print(FenwickTree2D<int> &ft) {
  cout << endl;
  for (int i = 1; i <= ft.N; i++) {
    for (int j = 1; j <= ft.M; j++) {
      cout << ft.query(i, j) << ' ';
    }
    cout << endl;
  }
}

int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int dy[] = {0, -1, 1, 0, -1, 1, 0, -1, 1};

int main(){
  std::ios_base::sync_with_stdio(false); cin.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  FenwickTree2D<int> ft(n, m);

  int x, y;
  for (int i = 1; i <= n; i++) {
    string line; cin >> line;
    for (int j = 1; j <= m; j++) {
      if (line[j - 1] == 'X') {
        ft.update(i, j, i, j, 1);
      }
      if (line[j - 1] == 'S') {
        x = i;
        y = j;
      }
    }
  }

  vvi vis(n + 1, vi(m + 1, 0));
  vis[x][y] = 1;
  vector<pii> pos = {{x, y}};
  
  for (int bomb = 1; bomb <= k; bomb++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    ft.update(a, b, c, d, 1);
    if (DBG) print(ft);
    vector<pii> npos;
    for (pii p : pos) {
      for (int di = 0; di < 9; di++) {
        int x2 = p.X + dx[di];
        int y2 = p.Y + dy[di];
        if (x2 <= 0 || x2 > n || y2 <= 0 || y2 > m) continue;
        if (vis[x2][y2]) continue;
        if (ft.query(x2, y2)) continue;
        vis[x2][y2] = 1;
        npos.push_back({x2, y2});
        if (DBG) cout << x2 << ' ' << y2 << endl;
      }
    }
    pos = npos;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!vis[i][j]) continue;
      if (ft.query(i, j) == 0) {
        cout << i << ' ' << j << endl;
        return 0;
      }
    }
  }
  cout << -1 << endl;
}
