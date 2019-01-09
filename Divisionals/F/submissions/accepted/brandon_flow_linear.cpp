#include<iostream>

using namespace std;

int main(){
   int m, n; cin >> m >> n;
   int sum = 0;
   for(int i = 0; i < m; i++){
      int l; cin >> l;
      sum += l;
   }
   int e = 1;
   while(e*n < sum)
      e++;
   cout << e << endl;
   
   return 0;
}
