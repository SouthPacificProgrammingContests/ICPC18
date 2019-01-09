// A very dumb solution that should still pass...
// It is basically as slow as I can possibly make it...

#include <bits/stdc++.h>
using namespace std;

int main(){
  string clue;
  getline(cin, clue);
  vector<bool> start_of_word(2*clue.size()+1, false);
  start_of_word[0] = true;

  for(int i=0;i<(int)clue.size();i++)
    if(clue[i] == ' '){
      start_of_word[i] = true;
      clue.erase(begin(clue)+i);
    }
  start_of_word[clue.size()] = true;
  int W; cin >> W;

  for(int i=0;i<W;i++){
    string soln; cin >> soln;
    bool should_print = false;
    for(int j1=0;j1<(int)clue.size();j1++)
      for(int j2=1;j2<=(int)clue.size();j2++){
	string this_clue = clue.substr(j1,j2);
	string this_soln = soln;
	bool good = true;
	
	if(this_clue == this_soln) good = false;
	if(!start_of_word[j1]) good = false;
	if(!start_of_word[j1+j2]) good = false;
	if(this_clue.size() != this_soln.size()) good = false;
	sort(begin(this_clue), end(this_clue));
	sort(begin(this_soln), end(this_soln));
	if(this_clue != this_soln) good = false;
	
	if(good) should_print = true;
      }
    if(should_print) cout << soln << endl;
  }
}
