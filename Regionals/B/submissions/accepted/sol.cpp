#include <iostream>
#include <vector>

using namespace std;

namespace solution {

vector<int> makeLPS(string S) {
    vector<int> lps(S.size(), -1);
    lps[0] = 0;
    int cur = 0;
    int i = 1;
    while(i < S.size()) {
        if(S[i] == S[cur]) {
            // Matching characters, so extend the current LPS
            cur++;
            lps[i] = cur;
            i++;
        } else {
            // Mismatch, fall back.
            if(cur != 0) {
                // Fall back to LPS for S[0..cur]
                // This is zero indexed, which is why we have -1
                cur = lps[cur-1];
            } else {
                // Complete mistmatch, so LPS is 0.
                // Try from next position
                lps[i] = 0;
                i++;
            }
        }
    }
    //for(auto x: lps) {
    //    cerr << " " << x;
    //}
    //cerr << "\n";
    return lps;
}

int kmp(string T, string S) {
    int longest = 0;
    auto lps = makeLPS(S);
    int i = 0;
    int cur = 0;
    while(i < T.size()) {
        longest = max(longest, cur);
        if(cur == S.size()) {
            // Return found!
            break;
        }
        if(T[i] == S[cur]) {
            // Matching chars, so extend
            i++; cur++;
        } else {
            // Mismatch, fall back.
            if(cur != 0) {
                cur = lps[cur-1];
            } else {
                // Completely mismatched, start fresh
                i++;
                cur = 0; // Not necessary since cur = 0 when we get here anyway
            }
        }
    }
    longest = max(longest, cur);
    return longest;
}

int solve(string S) {
    if(S.size() <= 3) {
        return S.size();
    }
    string v[2];
    for(int i = 0; i < S.size(); i++) {
        v[i&1].push_back(S[i]);
    }
    int a1 = kmp(S, v[0])*2;
    int a2 = kmp(S, v[1])*2+1;
    int ans = max(a1, a2);
    return min(ans, (int)S.size());
}

} // End namespace solution


int main(void) {
    string S;
    cin >> S;
    cout << solution::solve(S) << "\n";
}
