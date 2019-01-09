#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int di[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int dj[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

bool is_set(const vector<ull>& v, int bit){
    return (v[bit/64] >> (bit&63)) & 1;
}

void fill_range(vector<ull>& v, int left, int right){
    /*
    for(int i=left;i<right;i++)
        v[i/64] |= (1ull << (i%64)); 
        
    return;*/
    int l_ind = left / 64, r_ind = right / 64;
    
    if(l_ind == r_ind){
        ull ones = (1ull << (right - left)) - 1;
        v[l_ind] |= ones << (left % 64);
        return;
    }
    
    if(left % 64){
        ull l_ones = (1ull << ((l_ind+1)*64 - left))-1;
        v[l_ind] |= (l_ones << (left % 64));
    } else l_ind--;
    
    fill(begin(v)+l_ind+1,begin(v)+r_ind,ULLONG_MAX);
    
    if(right % 64){
        ull r_ones = (1ull << (right - r_ind*64))-1;
        v[r_ind] |= r_ones;
    }
}

void read_and_update(vector<vector<ull> >& painted, bool transpose, int m, int n){
    int r1,c1,r2,c2; cin >> r1 >> c1 >> r2 >> c2;
    if(transpose){
        swap(r1,c1);
        swap(r2,c2);
    }
    
    r1--; r2--; c1--; c2--;
    for(int i=r1;i<=r2;i++)
        fill_range(painted[i], c1, c2+1);
    
    /*
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            cout << is_set(painted[i],j);
        cout << endl;
    }
    cout << endl;*/
}

int main(){
    ios_base::sync_with_stdio(false);
    
    int m, n, k; cin >> m >> n >> k;
    
    vector<string> A(m);
    for(auto& x : A) cin >> x;
    
    bool transpose = (m > n);
    if(transpose){
        vector<string> trans(n, string(m,'-'));
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                trans[j][i] = A[i][j];
        A = trans;
        swap(m,n);
    }

    vector<vector<ull> > painted(m, vector<ull>(n/64+3));
    vector<vector<int> > D(m, vector<int>(n,-1));
    
    queue< pair<int,int> > q;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++){
            if(A[i][j] == 'S'){
                q.emplace(i,j);
                D[i][j] = 0;
            }
            if(A[i][j] == 'X')
                fill_range(painted[i], j, j+1);
        }
        
    int last_read = 0;    
    while(!q.empty()){
        pair<int,int> t = q.front(); q.pop();
        if(D[t.first][t.second] >= last_read){
            if(last_read++ < k)
                read_and_update(painted, transpose, m, n);
            else break;
        }
        
        for(int k=0;k<8;k++){
            int nI = t.first+di[k], nJ = t.second+dj[k];
            if(!(0 <= nI && nI < m && 0 <= nJ && nJ < n)) continue;
            if(D[nI][nJ] != -1) continue;
            if(!is_set(painted[nI], nJ)){
                D[nI][nJ] = D[t.first][t.second]+1;
                q.emplace(nI, nJ);
            }
        }
    }
    
    for(;last_read<k;last_read++)
        read_and_update(painted, transpose, m, n);
    
    if(transpose){
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(!is_set(painted[j],i) && D[j][i] != -1){
                    cout << i+1 << " " << j+1 << endl;
                    cerr << D[j][i] << endl;
                    return 0;
                }
    } else {
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(!is_set(painted[i],j) && D[i][j] != -1){
                    cout << i+1 << " " << j+1 << endl;
                    cerr << D[i][j] << endl;
                    return 0;
                }
    }
    
    cout << -1 << endl;
}
