#include <bits/stdc++.h>

using namespace std;

template <typename T>
using V = vector<T>;

typedef long double ld;
typedef long long ll;

#define FO(i, N) for (int (i) = 0; (i) < (N); ++(i))
#define FOll(i, N) for (ll (i) = 0; (i) < (N); ++(i))
#define READALL(c) for (auto &e : c) { cin >> e; }
#define PRINTALL(c) for (const auto &e : c) { cout << e << "\t"; } cout << "\n";
#define MP(x, y) (make_pair((x), (y)))
#define MT(...) make_tuple(__VA_ARGS__)
#define G(i, x) get<i>(x)
#define ALL(x) begin(x), end(x)

int main() {
	string clue;
	getline(cin, clue);
	V<string> words;
	stringstream ss(clue);
	string word;
	while (ss >> word) words.push_back(word);
	int S;
	cin >> S >> ws;
	FO(s, S) {
		string sol;
		getline(cin, sol);
		multiset<char> sol_set(ALL(sol));
		bool g = 0;
		FO(i, words.size()) {
			string subwords;
			multiset<char> subwords_set;
			for (int j = i; j < words.size(); ++j) {
				subwords += words[j];
				subwords_set.insert(ALL(words[j]));
				if (subwords == sol) continue;
				if (subwords_set == sol_set) {
					g = 1;
					break;
				}
			}
		}
		if (g) {
			cout << sol << endl;
			return 0;
		}
	}
}
