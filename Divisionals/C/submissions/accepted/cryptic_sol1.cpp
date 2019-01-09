//
//  cryptic_sol1.cpp
//
//  Problem setter's code for "Cryptic Clues" for South Pacific round of ICPC
//
//  Based on string sorting approach to anagrams, brute forcing all possible
//  consecutive sequences of whole words
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <utility>

using namespace std;

int main()
{
    // Read clue into line then put clue words in vector
    string clue;
    getline(cin, clue);
    
    vector<string> clue_words;
    istringstream is(clue);
    string word;
    while(is >> word) clue_words.push_back(word);
    int n_clue_words = (int)clue_words.size();
    
    // Read the list of associated words and form multimap from sorted versions
    // to associated words
    int W;
    cin >> W;
    multimap<string, string> anagram_map;
    for(int i = 0; i < W; i++)
    {
        string associated_word, sorted;
        cin >> associated_word;
        sorted = associated_word;
        sort(sorted.begin(), sorted.end());
        anagram_map.insert(make_pair(sorted, associated_word));
    }
    
    // Check all consecutive word sequences for anagram in word list
    // noting that something is _not_ considered an anagram of itself
    string answer;
    for(int i = 0; i < n_clue_words; i++)
    {
        string clue_part;
        for(int j = i; j < n_clue_words; j++)
        {
            clue_part += clue_words[j];
            string sorted_clue_part = clue_part;
            sort(sorted_clue_part.begin(), sorted_clue_part.end());
            
            auto begin_end = anagram_map.equal_range(sorted_clue_part);
            
            if(begin_end.first != begin_end.second)
            {
                for(auto possible = begin_end.first;
                    possible != begin_end.second; ++possible)
                {
                    if(possible->second != clue_part)
                    {
                        cout << possible->second << endl;
                        return 0;
                    }
                }
            }
        }
    }
    
    // Shouldn't get here as would indicate answer not found
    return 0;
}
