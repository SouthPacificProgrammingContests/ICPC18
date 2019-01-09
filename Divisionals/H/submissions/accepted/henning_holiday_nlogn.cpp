#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void parseInput(vector<int> &temp)
{
    int n;
    cin >> n;
    temp.resize(n);
    for ( int i = 0; i < n; i++ )
        cin >> temp[i];
}

// map temperatures to [0..k[, where k is number of distinct values; returns k
int minimizeValues(vector<int> &temp)
{
    unordered_map<int,int> minMap;
    int k = 0;
    for ( int &t : temp )
    {
        if ( minMap.count(t) == 0 )
            minMap[t] = k++;
        t = minMap[t];
    }
    return k;
}

// are x days sufficient to experience each of the k different temperatures?
bool eachTempCovered(const vector<int> &temp, int k, int x)
{
    vector<int> exp(k); // store #of occurences for each temperature experienced
    // initialize exp with first x days
    for ( int i = 0; i < x; i++ )
        exp[temp[i]]++;
    // check that each temperature is covered initially
    for ( int i = 0; i < k; i++ )
        if ( exp[i] == 0 )
            return false;
    // shift period of stay & keep checking
    int max_start = temp.size() - x;
    for ( int start = 0; start < max_start; start++ )
    {
        exp[temp[start]]--;
        exp[temp[start+x]]++;
        // only temperature that could be missed is on start day
        if ( exp[temp[start]] < 1 )
            return false;
    }
    return true;
}

int main()
{
    vector<int> temp;
    parseInput(temp);
    int k = minimizeValues(temp);
    // binary search for minimal number of days
    int lower = k; // lower bound, inclusive
    int upper = temp.size(); // upper bound, inclusive
    while ( lower < upper )
    {
        int mid = (lower + upper) / 2;
        if ( eachTempCovered(temp, k, mid) )
            upper = mid;
        else
            lower = mid + 1;
    }
    cout << lower << endl;
}
