#include <bits/stdc++.h>
using namespace std;

const int di[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int dj[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

int main(){
    int m, n, k; cin >> m >> n >> k;
    
    vector<string> A(m);
    for(auto& x : A) cin >> x;
        
    vector<vector<int> > when(m, vector<int>(n, k+1));
    
    vector<set<int> > left(min(m,n));
    for(auto& S : left)
        for(int i=0;i<max(m,n);i++)
            S.insert(i);
    
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            if(A[i][j] == 'X'){
                when[i][j] = 0;
                if(m > n) left[j].erase(i);
                else left[i].erase(j);
            }

    
    for(int me=0;me<k;me++){
        int r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        if(m > n){
            swap(r1,c1);
            swap(r2,c2);
        }
        for(int i=r1;i<=r2;i++){
            auto it = left[i].lower_bound(c1);
            auto st = it;
            while(it != left[i].end() && (*it) <= c2){
                (m > n ? when[*it][i] : when[i][*it]) = me+1;
                ++it;
            }
            left[i].erase(st, it);
        }
    }
    
    vector<vector<int> > D(m, vector<int>(n, -1));
    
    queue< pair<int,int> > q;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            if(A[i][j] == 'S'){
                q.emplace(i,j);
                D[i][j] = 0;
            }
    
    int longest_distance = 0;
    while(!q.empty()){
        pair<int,int> t = q.front(); q.pop();
        longest_distance = D[t.first][t.second];
        for(int k=0;k<8;k++){
            int nI = t.first+di[k], nJ = t.second+dj[k];
            if(!(0 <= nI && nI < m && 0 <= nJ && nJ < n)) continue;
            if(D[nI][nJ] != -1) continue;
            int paint = when[nI][nJ], d = D[t.first][t.second]+1;
            if(paint <= d) continue;
            D[nI][nJ] = d;
            q.emplace(nI, nJ);
        }
    }
    
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            if(when[i][j] == k+1 && (D[i][j] != -1 && D[i][j] <= k)){
                //assert(D[i][j] < 500);
                cout << i+1 << " " << j+1 << endl;
                return 0;
            }
    
    cout << -1 << endl;
}
