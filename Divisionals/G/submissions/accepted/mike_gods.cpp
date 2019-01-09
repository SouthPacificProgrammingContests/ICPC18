//
//  rubiks.cpp
//
//  A moderator's attempted solution for "God's Number" SPP part of 2018 ICPC
//
//  Undoes last operation by doing it 3 times, undoes now last, ...
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    for(auto p = s.rbegin(); p != s.rend(); ++p) cout << *p << *p << *p;
    cout << endl;
    return 0;
}
