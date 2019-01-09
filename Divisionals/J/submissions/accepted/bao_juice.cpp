#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Fraction {
  int nume, deno;

  Fraction(int nume, int deno) {
    this->nume = nume;
    this->deno = deno;
  }
};

int N, C;
vector<Fraction> coins;

void fetch_input() {
  cin >> N >> C;
  for (int i = 0; i < C; ++i) {
    int nume, deno;
    cin >> nume >> deno;
    coins.push_back(Fraction(nume, deno));
  }
}

int gcd(int a, int b) {
  if (a == 0 || b == 0) return a + b;
  return gcd(b, a % b);
}

void transform_input() {
  int lcm = 1;
  for (Fraction &coin : coins) {
    int div = gcd(lcm, coin.deno);
    lcm = lcm / div * coin.deno;
  }

  for (Fraction &coin : coins) {
    coin.nume *= lcm / coin.deno;
    coin.deno = lcm;
  }
  N *= lcm;
}

int get_optimal_step() {
  queue<int> payable_amount;
  unordered_map<int, int> visited;
  payable_amount.push(0);
  visited.emplace(0, 0);

  while (!payable_amount.empty()) {
    int amount = payable_amount.front();
    payable_amount.pop();
    int n_coins = visited[amount];

    if (amount == N) {
      return n_coins;
    }

    for (Fraction &coin : coins) {
      int next_amount = amount + coin.nume;
      if (next_amount <= N && visited.find(next_amount) == visited.end()) {
        visited[next_amount] = n_coins + 1;
        payable_amount.push(next_amount);
      }
    }
  }
  return -1;
}

void solve() {
  transform_input();
  cout << get_optimal_step() << endl;
}

int main() {
  fetch_input();
  solve();
  return 0;
}
