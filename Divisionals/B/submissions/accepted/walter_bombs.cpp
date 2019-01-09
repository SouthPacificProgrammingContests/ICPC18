#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int,int> pi;
typedef pair<pi,int> pii;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;

vvpi multree, addtree;

int query2(vvpi &tree, int x, int y) {
  int mul = 0, add = 0;
  for (int j=y ; j>0 ; j -= j&-j) {
    mul += tree[x][j].first;
    add += tree[x][j].second;
  }
  return (mul * y) + add;
}

int query1(int x, int y) {
  int mul = 0, add = 0;
  for (int i=x ; i>0 ; i -= i&-i) {
    mul += query2(multree, i, y);
    add += query2(addtree, i, y);
  }
  return (mul * x) + add;
}

int query(int x1, int x2, int y1, int y2) {
  return query1(x2, y2) - query1(x1-1, y2) - query1(x2, y1-1) + query1(x1-1, y1-1);
}

void update2(vvpi &tree, int x, int y, int mul, int add) {
  for (int i=x ; i<(int)tree.size() ; i += i&-i)
    for (int j=y ; j<(int)tree[i].size() ; j += j&-j) {
      tree[i][j].first += mul;
      tree[i][j].second += add;
    }
}

void update1(int x, int y1, int y2, int mul, int add) {
  update2(multree, x, y1, mul, -mul * (y1 - 1));
  update2(multree, x, y2, -mul, mul * y2);
  update2(addtree, x, y1, add, -add * (y1 - 1));
  update2(addtree, x, y2, -add, add * y2);
}

void update(int x1, int x2, int y1, int y2, int by) {
  update1(x1, y1, y2, by, -by * (x1 - 1));
  update1(x2, y1, y2, -by, by * x2);
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  multree = vvpi(n+1, vpi(m+1));
  addtree = vvpi(n+1, vpi(m+1));
  string grid[n];
  pii start;
  for (int i=0 ; i<n ; i++) {
    cin >> grid[i];
    for (int j=0 ; j<m ; j++)
      if (grid[i][j] == 'S')
        start = pii(pi(i, j), 0);
  }
  queue<pii> que;
  que.push(start);
  int z = -1, current = -1;
  while (!que.empty()) {
    pii front = que.front();
    que.pop();
    int x = front.first.first;
    int y = front.first.second;
    z = front.second;
    if (z != current) {
      current = z;
      if (z < k) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        update(x1, x2, y1, y2, 1);
      } else break;
    }
    for (int dx=-1 ; dx<2 ; dx++)
      for (int dy=-1 ; dy<2 ; dy++) {
        int xx = x+dx, yy = y+dy;
        if (0 <= xx && xx < n && 0 <= yy && yy < m && grid[xx][yy] == '.' && query(xx+1, xx+1, yy+1, yy+1) == 0) {
          que.push(pii(pi(xx, yy), z+1));
          grid[xx][yy] = 'S';
        }
      }
  }
  while (z+1 < k) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    update(x1, x2, y1, y2, 1);
    z += 1;
  }
  for (int i=0 ; i<n ; i++)
    for (int j=0 ; j<m ; j++)
      if (grid[i][j] == 'S' && query(i+1, i+1, j+1, j+1) == 0) {
        cout << i+1 << ' ' << j+1 << endl;
        return 0;
      }
  cout << -1 << endl;
  return 0;
}
