#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

struct Query {
  string type;
  int X, Y;

  Query(const string &type, int X, int Y) {
    this->type = type;
    this->X = X;
    this->Y = Y;
  }
};

typedef pair<int, int> pii;

int N, F, Q;
set<pii> friends;
vector<Query> queries;

void fetch_input() {
  cin >> N >> F >> Q;
  for (int i = 0; i < F; ++i) {
    int X, Y;
    cin >> X >> Y;
    friends.insert(make_pair(--X, --Y));
  }
  for (int i = 0; i < Q; ++i) {
    string type;
    int X, Y;
    cin >> type >> X >> Y;
    queries.push_back(Query(type, --X, --Y));
  }
}

void process_end_queries() {
  for (int i = 0; i < Q; ++i) {
    if (queries[i].type == "E") {
      friends.erase(make_pair(queries[i].X, queries[i].Y));
    }
  }
}

int get_group(vector<int> &group, int vertex) {
  if (group[vertex] == vertex) {
    return vertex;
  }
  group[vertex] = get_group(group, group[vertex]);
  return group[vertex];
}

void initialize_dsu(vector<int> &group) {
  for (int i = 0; i < group.size(); ++i) {
    group[i] = i;
  }
  for (const pii &fr : friends) {
    int gX = get_group(group, fr.first);
    int gY = get_group(group, fr.second);
    group[gY] = gX;
  }
}

void solve() {
  process_end_queries();

  vector<int> group(N);
  initialize_dsu(group);

  vector<bool> answers;
  for (int i = Q - 1; i >= 0; --i) {
    if (queries[i].type == "E") {
      int gX = get_group(group, queries[i].X);
      int gY = get_group(group, queries[i].Y);
      group[gY] = gX;
    } else {
      int gX = get_group(group, queries[i].X);
      int gY = get_group(group, queries[i].Y); 

      answers.push_back(gX == gY);
    }
  }

  for (int i = (int) answers.size() - 1; i >= 0; --i) {
    cout << (answers[i] ? "YES" : "NO") << "\n";
  }
}

int main() {
  fetch_input();
  solve();
  return 0;
}
