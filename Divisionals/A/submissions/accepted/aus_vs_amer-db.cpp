#include <bits/stdc++.h>
using namespace std;

const int dom[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

bool valid(int d, int m, int y){
    if(!(1 <= m && m <= 12)) return false;
    if(!(1 <= d && d <= dom[m-1])) return false;
    if(m == 2 && d == 29) return y % 4 == 0;
    return true;
}

int main(){
    int n; cin >> n;
    
    vector<vector<int> > A(n, vector<int>(3));
    
    for(int i=0;i<n;i++){
        char c;
        cin >> A[i][0] >> c >> A[i][1] >> c >> A[i][2];
    }
    
    vector<vector<int> > ans;
    int perm[3] = {0,1,2};
    do {
        bool good = true;
        for(int i=0;i<n;i++)
            if(!valid(A[i][perm[0]], A[i][perm[1]], A[i][perm[2]]))
                good = false;
        if(good) ans.emplace_back(perm, perm+3);
    } while(next_permutation(perm,perm+3));
    
    if(ans.empty()){ cout << "IMPOSSIBLE" << endl; }
    else if(ans.size() > 1) { cout << "UNSURE" << endl; }
    else {
        string vals = "DMY", output = "XX/XX/XX";
        for(int i=0;i<3;i++)
            fill_n(begin(output)+3*ans[0][i],2,vals[i]);
        cout << output << endl;
    }
}
