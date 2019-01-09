#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

const int maxn = 1<<18;

vi tree1[maxn], qs[maxn];
char tree2[maxn];
int tree3[maxn], pred[maxn], RANK[maxn], color[maxn], anc[maxn], cur[maxn], cnt;

int find(int x) {
  if (pred[x] != x)
    pred[x] = find(pred[x]);
  return pred[x];
}

void unite(int x, int y) {
  int xr = find(x);
  int yr = find(y);
  if (RANK[xr] >= RANK[yr]) {
    pred[yr] = xr;
    if (RANK[xr] == RANK[yr])
      ++RANK[xr];
  } else
    pred[xr] = yr;
}

void dfs(int x) {
  anc[x] = x;
  color[x] = 1;
  for (unsigned int i=0 ; i<tree1[x].size() ; i++) {
    int y = tree1[x][i];
    cur[x] = y;
    dfs(y);
  }
  color[x] = 2;
  for (unsigned int i=0 ; i<qs[x].size() ; i++) {
    int y = qs[x][i];
    if (color[y] == 2) {
      int ya = anc[find(y)];
      int lca = tree3[ya];
      if (lca == x) {
        if (tree2[ya] == 'L')
          ++cnt;
      } else if (lca != 0) {
        int xa = cur[lca];
        if (tree2[min(xa, ya)] == 'L')
          ++cnt;
      }
    }
  }
  for (unsigned int i=0 ; i<tree1[x].size() ; i++)
    unite(x, tree1[x][i]);
  anc[find(x)] = x;
}

int main() {
  int n, q;
  cin >> n >> q;
  tree1[1] = vi();
  tree2[1] = ' ';
  tree3[1] = 0;
  for (int i=2 ; i<=n+1 ; i++) {
    char lp;
    int v;
    cin >> lp >> v;
    tree1[i] = vi();
    tree2[i] = lp;
    tree3[i] = v;
    tree1[v].push_back(i);
  }
  for (int i=1 ; i<=n+1 ; i++)
    qs[i] = vi();
  for (int i=0 ; i<q ; i++) {
    int u, v;
    cin >> u >> v;
    qs[u].push_back(v);
    qs[v].push_back(u);
  }
  for (int i=1 ; i<=n+1 ; i++) {
    pred[i] = i;
    RANK[i] = 1;
    color[i] = 0;
    anc[i] = 0;
    cur[i] = 0;
  }
  cnt = 0;
  for (int i=1 ; i<=n+1 ; i++)
    if (color[i] == 0)
      dfs(i);
  cout << cnt << endl;
  return 0;
}