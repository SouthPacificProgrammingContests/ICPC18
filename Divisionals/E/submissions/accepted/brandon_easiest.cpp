#include<iostream>

using namespace std;

struct Prob{
   string s;
   int a,b,c;
   bool operator<(const Prob & X) const {
      if(a+b+c == X.a + X.b + X.c)
	 return a < X.a;
      return a+b+c < X.a + X.b + X.c;
   }
};

int main(){
   int P; Prob cur, nxt;
   cin >> P;
   cin >> cur.s >> cur.a >> cur.b >> cur.c;
   for(int i = 1; i < P; i++){
      cin >> nxt.s >> nxt.a >> nxt.b >> nxt.c;
      if(nxt < cur)
	 cur = nxt;
   }
   cout << cur.s << endl;
   return 0;
}
