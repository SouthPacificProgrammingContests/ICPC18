//
//  cryptic_sol2.cpp
//
//  Setter's alternative solution for "Cryptic Clues" South Pacific ICPC
//
//  Based on letter frequency approach to anagrams, crude try all approach,
//  based on unsorted vectors, with clue input read word by word so as to
//  differ from own first solution

#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <utility>
#include <sstream>

using namespace std;

typedef vector<int> vi;
typedef pair<vi, string> pvis;


int main()
{
    // Read clue words
    string clue_word;
    vector<string> clue_words;
    for(;;)
    {
        cin >> clue_word;
        if(isdigit(clue_word[0])) break; // read number, so past clue
        clue_words.push_back(clue_word);
    }
    int n_clue_words = (int) clue_words.size();
    
    // Read associated words into vector of pairs of frequency counts and words
    istringstream is(clue_word);
    int W;
    is >> W;
    
    vector<pvis> dictionary;
    
    for(int i = 0; i < W; i++)
    {
        vector<int> frequency_count(26);
        string associated_word;
        cin >> associated_word;
        int m = (int) associated_word.size();
        for(int j = 0; j < m; j++) frequency_count[associated_word[j] - 'a']++;
        dictionary.push_back(make_pair(frequency_count, associated_word));
    }
    
    // Brute force every clue word sequence checking every dictionary entry
    for(int i = 0; i < n_clue_words; i++)
    {
        string clue_part;
        vector<int> frequency_count(26);
        for(int j = i; j < n_clue_words; j++)
        {
            clue_part += clue_words[j];
            int m = (int) clue_words[j].size();
            for(int k = 0; k < m; k++)
                frequency_count[clue_words[j][k] - 'a']++;
            
            for(int k = 0; k < W; k++)
            {
                if((frequency_count == dictionary[k].first) &&
                   (clue_part != dictionary[k].second))
                {
                    cout << dictionary[k].second << endl;
                    return 0;
                }
            }
        }
    }

    
    // Shouldn't get here as would mean didn't find solution
    return 0;
}
