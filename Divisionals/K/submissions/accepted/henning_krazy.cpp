#include <iostream>
#include <vector>
#include <array>
#include <bitset>

#define MAX_LOCATION 1000

using namespace std;

typedef array<int,2> Road;
struct Input
{
    int n;
    vector<Road> twoway;
    vector<Road> oneway;
};

void parseInput(Input &input)
{
    int x, y;
    cin >> input.n >> x >> y;
    input.twoway.resize(x);
    input.oneway.resize(y);
    for ( int i = 0; i < x; i++ )
        cin >> input.twoway[i][0] >> input.twoway[i][1];
    for ( int i = 0; i < y; i++ )
        cin >> input.oneway[i][0] >> input.oneway[i][1];
}

typedef bitset<MAX_LOCATION+1> NodeSet;

class Graph
{
    vector<vector<int>> neighbors;
public:
    Graph(int n) { neighbors.resize(n); }
    void addEdge(int u, int v) { neighbors[u].push_back(v); }
    NodeSet getReachable(int from) const;
};

NodeSet Graph::getReachable(int from) const
{
    NodeSet visited;
    vector<int> stack = { from };
    while ( !stack.empty() )
    {
        int node = stack.back(); stack.pop_back();
        if ( !visited[node] )
        {
            visited[node] = true;
            for ( int neighbor : neighbors[node] )
                stack.push_back(neighbor);
        }
    }
    return visited;
}

int main()
{
    Input input;
    parseInput(input);
    // build graph for legal travel
    Graph g(input.n + 1);
    for ( const Road &road : input.twoway )
    {
        g.addEdge(road[0], road[1]);
        g.addEdge(road[1], road[0]);
    }
    for ( const Road &road : input.oneway )
        g.addEdge(road[0], road[1]);
    // compute reachability
    NodeSet legalLocations = g.getReachable(1);
    // allow travel in the wrong direction
    for ( const Road &road : input.oneway )
        g.addEdge(road[1], road[0]);
    NodeSet illegalLocations = g.getReachable(1);
    // print result
    for ( int loc = 1; loc <= input.n; loc++ )
        if ( legalLocations[loc] )
            cout << "No Ticket" << endl;
        else if ( illegalLocations[loc] )
            cout << "Ticket" << endl;
        else
            cout << "Impossible" << endl;
}
