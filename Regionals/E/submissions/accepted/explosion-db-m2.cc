// Explosive Wiring
// Author: Darcy Best
// Complexity: O(m^2)
//
// EXPECTED_RESULT: CORRECT

#include <bits/stdc++.h>
using namespace std;

vector<int> value;               // The value of the i'th wire
vector<vector<bool> > intersect; // Do the wires intersect?
vector<int> right_end;           // Who is my right endpoint?
vector<vector<int> > adj;        // Which edges are adjacent to me? (and I'm the .first)
vector<pair<int,int> > edge;     // Who are the wires in this edge?

vector<vector<int> > DP;

int f(int idx, int ceiling){
  int& x = DP[idx][ceiling];
  if(x >= 0) return x;

  int c1 = edge[ceiling].first, c2 = edge[ceiling].second;
  if(c1 == idx || c2 == idx || right_end[c1] == idx || right_end[c2] == idx) return x = 0; // Empty range

  x = f(idx+1, ceiling); // Don't use this wire
  
  if(right_end[idx] != idx && !intersect[idx][c1] && !intersect[idx][c2]){ // Use this wire
    for(int e_idx : adj[idx]){
      int you = edge[e_idx].second;
      if(intersect[you][c1] || intersect[you][c2]) continue;
      x = max(x,
            value[idx] + value[you] + f(idx+1, e_idx) + f(you+1, e_idx) +
            f(min(right_end[idx], right_end[you])+1, e_idx) +
            f(max(right_end[idx], right_end[you])+1, ceiling));
    }
  }  

  return x;
}

struct Point {
  int x, y;
};
Point operator-(Point p, Point q){ return {p.x-q.x, p.y-q.y}; }
int cross(Point p, Point q){ return p.x*q.y - p.y*q.x; }

bool in_bounding_box(Point p, Point q, Point r){ // Is r in box?
  return min(p.x,q.x) <= r.x && r.x <= max(p.x,q.x) &&
    min(p.y,q.y) <= r.y && r.y <= max(p.y,q.y);
}

int dir(Point p, Point q, Point r){
  int val = cross(q-p, r-q);
  if(val == 0) return (in_bounding_box(p,q,r) ? 2 : 0); // 0 is bad... 2 is on line
  return (val < 0 ? -1 : 1);
}

bool lines_intersect(pair<Point, Point> L1, pair<Point, Point> L2){
  int d1 = dir(L1.first, L1.second, L2.first), d2 = dir(L1.first, L1.second, L2.second);
  int d3 = dir(L2.first, L2.second, L1.first), d4 = dir(L2.first, L2.second, L1.second);

  return max({d1,d2,d3,d4}) == 2 || (d1*d2 == -1 && d3*d4 == -1);
}

bool polylines_intersect(const vector<Point>& p, const vector<Point>& q){
  for(int i=0;i+1<(int)p.size();i++)
    for(int j=0;j+1<(int)q.size();j++)
      if(lines_intersect(make_pair(p[i], p[i+1]), make_pair(q[j], q[j+1])))
        return true;
  return false;
}

int main(){
  int n; cin >> n;

  vector<vector<Point> > lines(n);

  vector<int> orig_values(n);
  vector<pair<int,int> > who;
  for(int i=0;i<n;i++){
    int p; cin >> orig_values[i] >> p;
    lines[i].resize(p);
    for(auto& pt : lines[i])
      cin >> pt.x >> pt.y;
    who.emplace_back(lines[i].front().x, i);
    who.emplace_back(lines[i].back().x , i);
  }
  sort(begin(who), end(who));

  for(int i=0;i<2*n;i++)
    value.push_back(orig_values[ who[i].second ]);

  vector<int> the_right(n, -1);
  right_end.resize(2*n+1, 2*n); // The 2*n is so that right_end[2*n] == 2*n
  for(int i=2*n-1;i>=0;i--){
    if(the_right[ who[i].second ] == -1) the_right[ who[i].second ] = i;
    right_end[i] = the_right[ who[i].second ];
  }

  intersect.assign(2*n+1, vector<bool>(2*n+1, false));
  adj.resize(2*n+1);

  for(int i=0;i<2*n;i++)
    for(int j=i+1;j<2*n;j++)
      if(polylines_intersect(lines[who[i].second], lines[who[j].second])){
        intersect[i][j] = intersect[j][i] = true;
        if(right_end[i] != i && right_end[j] != j){
          adj[i].push_back(edge.size());
          edge.emplace_back(i,j);
        }
    }
  edge.emplace_back(2*n, 2*n); // An overarching edge

  int m = edge.size();
  DP.assign(2*n+1, vector<int>(m, -1));

  cout << f(0, m-1) << endl;
}
