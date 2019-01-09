#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

enum Type {
  E,
  S
};

struct Input {
  Type t;
  int a, b;
};

int main()
{
  int n, f, q;
  std::cin >> n >> f >> q;

  std::vector<int> responses;
  std::vector<Input> edges(f);
  std::vector<Input> inputs;

  for (int i = 0; i < f; i++) {
    std::cin >> edges[i].a >> edges[i].b;
  }

  for (int i = 0; i < q; i++) {
    char c;
    Input in;
    std::cin >> c >> in.a >> in.b;
    in.t = ((c == 'E') ? E : S);
    inputs.push_back(in);
  }

  std::set<std::pair<int, int>> edges_to_remove;
  for (const auto &in : inputs) {
    if (in.t == E) {
      edges_to_remove.insert({in.a, in.b});
    }
  }

  edges.erase(std::remove_if(edges.begin(), edges.end(), [&edges_to_remove](Input edge) {
    return edges_to_remove.count({edge.a, edge.b});
  }), edges.end());

  std::reverse(inputs.begin(), inputs.end());

  std::vector<int> parent(n+1);
  std::iota(parent.begin(), parent.end(), 0);

  std::function<int(int)> GetParent = [&GetParent, &parent](int i) -> int {
    if (parent[i] == i) return i;
    return parent[i] = GetParent(parent[i]);
  };

  std::function<void(int,int)> UnionEdge = [&GetParent, &parent](int i, int j) {
    parent[GetParent(j)] = GetParent(i);
  };

  for (const auto &edge : edges) {
    UnionEdge(edge.a, edge.b);
  }

  for (const auto &q : inputs) {
    if (q.t == E) {
      UnionEdge(q.a, q.b);
    } else {
      responses.push_back(GetParent(q.a) == GetParent(q.b));
    }
  }

  std::reverse(responses.begin(), responses.end());

  for (auto r : responses) {
    std::cout << (r ? "YES" : "NO") << std::endl;
  }

}
