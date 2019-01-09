#include <string>
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
  std::string f;
  std::getline(std::cin, f);
  std::stringstream ss(f);
  std::string s;
  std::vector<std::string> in;
  while (ss >> s) {
    in.push_back(s);
  }
  std::vector<std::vector<int>> inx(in.size(), std::vector<int>(26));
  for (int i = 0; i < in.size(); i++) {
    for (char c : in[i]) {
      inx[i][c-'a']++;
    }
  }
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string cd;
    std::cin >> cd;
    std::vector<int> cx(26);
    for (char c : cd) {
      cx[c-'a']++;
    }
    for (int j = 0; j < inx.size(); j++) {
      std::string cand;
      std::vector<int> ox(26);
      for (int k = j; k < inx.size(); k++) {
        cand += in[k];
        for (int l = 0; l < 26; l++) {
          ox[l] += inx[k][l];
        }
        if (std::equal(ox.begin(), ox.end(), cx.begin())) {
          if (cand != cd) {
            std::cout << cd << std::endl;
            return 0;
          }
        }
      }
    }
  }
}
