#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int N, no_unique;
vector<int> temps;

void fetch_input() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int temp;
    cin >> temp;
    temps.push_back(temp);
  }
}

void build_next(vector<int> &next) {
  unordered_map<int, int> nearest_position;
  for (int i = N - 1; i >= 0; --i) {
    if (nearest_position.find(temps[i]) == nearest_position.end()) {
      next[i] = N;
    } else {
      next[i] = nearest_position[temps[i]];
    }
    nearest_position[temps[i]] = i;
  }
  no_unique = nearest_position.size();
}

void update_bit(vector<int> &bit, int i, int val) {
  for (++i; i <= bit.size(); i += i & -i) {
    bit[i - 1] += val;
  }
}

int get_bit(const vector<int> &bit, int i) {
  int result = 0;
  for (i = min(i + 1, N); i > 0; i -= i & -i) {
    result += bit[i - 1];
  }
  return result;
}

bool ok(const vector<int> &bit, int end_day) {
  return get_bit(bit, end_day) == no_unique;
}

int find_end_day(const vector<int> &bit, int start_day) {
  int l = start_day;
  int r = N;
  while (l < r) {
    int mid = (l + r) / 2;
    if (!ok(bit, mid)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l;
}

void solve() {
  vector<int> next(N);
  build_next(next);

  int min_consecutive_days = 0;
  vector<int> bit(N);
  for (int i = N - 1; i >= 0; --i) {
    update_bit(bit, i, 1);
    update_bit(bit, next[i], -1);

    min_consecutive_days = max(min_consecutive_days, find_end_day(bit, i) - i + 1);
  }

  cout << min_consecutive_days << endl;
}

int main() {
  fetch_input();
  solve();
  return 0;
}
