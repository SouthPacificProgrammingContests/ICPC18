//
//  dates.cpp
//
//  Moderator's attempt at "Australian vs American" SPPC 2018
//
//  Approach is to brute force all permutations of the 3 parts, checking
//  for each whether all "dates" in the list work as UK dates when so
//  permuted. In the event of unique such permutation unscramble it at end.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef vector<int> vi;

int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
    int n;
    cin >> n;
    vector<vi> dates(n, vi(3));
    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        dates[i][0] = (int)(10*(s[0] - '0') + s[1] - '0');
        dates[i][1] = (int)(10*(s[3] - '0') + s[4] - '0');
        dates[i][2] = (int)(10*(s[6] - '0') + s[7] - '0');
    }
    
    vi perm(3);
    for(int i = 0; i < 3; i++) perm[i] = i;
    
    vector<vi> viables;
    do
    {
        bool all_ok = true;
        for(int i = 0; i < n; i++)
        {
            vi date(3);
            for(int j = 0; j < 3; j++) date[j] = dates[i][perm[j]];
            int leap_days = 0;
            if((date[1] == 2) && ((date[2] % 4) == 0)) leap_days++;
            if((date[1] < 1) || (date[1] > 12) ||
               (date[0] < 1) ||
               (date[0] > days_per_month[date[1]] + leap_days))
            {
                all_ok = false;
            }
        }
        if(all_ok)
        {
            viables.push_back(perm);
        }
    }while(next_permutation(perm.begin(), perm.end()));
    
    if(viables.size() == 0)
    {
        cout << "IMPOSSIBLE\n";
    }
    else if(viables.size() != 1)
    {
        cout << "UNSURE\n";
    }
    else
    {
        vector<string> answer(3);
        string uk[3] = {"DD", "MM", "YY"};
        for(int i = 0; i < 3; i++)
        {
            answer[viables[0][i]] = string(uk[i]);
        }
        cout << answer[0] << "/" << answer[1] << "/" << answer[2] << endl;
    }
    
    return 0;
}
