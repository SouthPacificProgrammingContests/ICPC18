#include "cable_io.h"

using namespace std;

//--------------------------- PermutationBuilder --------------------

// class for efficient insertion of "next" integer before or after existing one
// essentially a double-linked list with random access by value
class PermutationBuilder
{
    struct IndexData
    {
        int before, after;
    };
    vector<IndexData> perm;
public:
    PermutationBuilder() : perm(1) {};

    void insertAfter(int n);
    void insertBefore(int n);
    vector<int> getPermutation() const;
};

void PermutationBuilder::insertAfter(int n)
{
    IndexData newData;
    newData.before = n;
    newData.after = perm[n].after;
    perm[n].after = perm.size();
    perm[newData.after].before = perm.size();
    perm.push_back(newData);
}

void PermutationBuilder::insertBefore(int n)
{
    insertAfter(perm[n].before);
}

vector<int> PermutationBuilder::getPermutation() const
{
    vector<int> result;
    int next = perm[0].after;
    while ( next )
    {
        result.push_back(next);
        next = perm[next].after;
    }
    return result;
}

//--------------------------- solve ---------------------------------

typedef int Index2D[2];

bool comparable(Index2D a, Index2D b)
{
    return (a[0] <= b[0] && a[1] <= b[1])
        || (a[0] >= b[0] && a[1] >= b[1]);
}

int solve(const Input &input)
{
    // construct reachability index - induced graph is prime-free and thus a permutation graph
    PermutationBuilder pb[2];
    // initial switchbox (numbered 1)
    pb[0].insertAfter(0);
    pb[1].insertAfter(0);
    for ( const Extension &e : input.extensions )
    {
        pb[0].insertAfter(e.target);
        if ( e.type == 'P' )
            pb[1].insertBefore(e.target);
        else
            pb[1].insertAfter(e.target);
    }
    vector<int> orders[2] = { pb[0].getPermutation(), pb[1].getPermutation() };
    // build inverted index
    const int BOXES = input.extensions.size() + 1;
    vector<Index2D> reachabilityIndex(BOXES + 1);
    for ( int i = 0; i < BOXES; i++ )
    {
        reachabilityIndex[orders[0][i]][0] = i;
        reachabilityIndex[orders[1][i]][1] = i;
    }
    // process queries
    int reachableCount = 0;
    for ( const Query &q : input.queries )
        if ( comparable(reachabilityIndex[q.from], reachabilityIndex[q.to]) )
            reachableCount++;
    return reachableCount;
}

int main()
{
    Input input;
    cin >> input;
    cout << solve(input) << endl;
}
