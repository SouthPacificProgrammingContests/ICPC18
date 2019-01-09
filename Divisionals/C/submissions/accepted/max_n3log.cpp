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

// An O(N^3 log N) solution.

int main() {
	string clue;
	getline(cin, clue);
	V<string> words;
	stringstream ss(clue);
	string word;
	while (ss >> word) words.push_back(word);
	map<V<int>, set<string>> M;
	// Replace set<string> with a set of trie nodes for O(N^2 log N).
	FO(i, words.size()) {
		string subwords;
		V<int> histo(26);
		for (int j = i; j < words.size(); ++j) {
			for (char c : words[j]) {
				histo[c-'a']++;
				subwords.push_back(c);
			}
			M[histo].insert(subwords);
		}
	}
	int S;
	cin >> S >> ws;
	FO(s, S) {
		string sol;
		getline(cin, sol);
		V<int> histo(26);
		for (char c : sol) histo[c-'a']++;
		if (M[histo].size() > 1) {
			cout << sol << endl;
			return 0;
		} else if (M[histo].size() == 1 && *M[histo].begin() != sol) {
			cout << sol << endl;
			return 0;
		}
	}
}
