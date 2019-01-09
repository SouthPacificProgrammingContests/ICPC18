#include <iostream>
using namespace std;

#define REP(i,n) for (int i = 0; i < n; i++)

int n, L, c;
string s;

int main() {
    cin >> n >> L;
    REP(i,n) {
      cin >> s;
      c += s.length();
    }

    bool ans;
    if (n == 1) {
      ans = (c == L);
    } else {
      int gap = (L - c);
      ans = (gap > 0) && (gap % (n - 1) == 0);
    }
    cout << (ans ? "Yes" : "No") << endl;
}
