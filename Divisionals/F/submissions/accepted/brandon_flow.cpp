#include<iostream>

using namespace std;

int main(){
   int m, n; cin >> m >> n;
   int sum = 0;
   for(int i = 0; i < m; i++){
      int l; cin >> l;
      sum += l;
   }
   cout << (sum+n-1)/n << endl;
   return 0;
}
