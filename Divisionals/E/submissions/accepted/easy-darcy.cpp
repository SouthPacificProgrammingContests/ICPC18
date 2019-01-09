#include <bits/stdc++.h>
using namespace std;

int main(){
  int P;
  cin >> P;

  string easiest_name;
  pair<int,int> easiest_rank(3*101,101);
  
  for(int i=0;i<P;i++){
    string prob;
    cin >> prob;
    int a, b, c;
    cin >> a >> b >> c;
    
    pair<int,int> my_rank(a+b+c,a);
    if(my_rank < easiest_rank){
      easiest_rank = my_rank;
      easiest_name = prob;
    }
  }
  
  cout << easiest_name << endl;
}
