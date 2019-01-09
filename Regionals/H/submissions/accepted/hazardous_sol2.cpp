//
//  hazardous_sol2.cpp
//
//  Problem setter's partly alternative code for "Hazardous Driving" for South Pacific round of ICPC
//
//  Based on binary search over BFS to find min max hazard rating followed
//  by Dijkstra from first solution
//

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll inf = (ll)400000 * (ll)2000000000;

struct edge
{
    int to;
    ll hazard;
    ll length;
    
    edge(int t, ll h, ll l) : to(t), hazard(h), length(l) {}
};
typedef vector<edge> adjacency_list;

// BFS to see if can reach to from from using no more than max_hazard
bool can_reach(int from, int to, vector<adjacency_list> &graph, ll max_hazard)
{
    int N = (int) graph.size();
    queue<int> q;
    vector<bool> seen(N+1);
    seen[from] = true;
    q.push(from);
    while(!seen[to] && !q.empty())
    {
        int here = q.front();
        q.pop();
        int n_adjs = (int) graph[here].size();
        for(int i = 0; i < n_adjs; i++)
        {
            edge &e = graph[here][i];
            if(!seen[e.to] && (e.hazard <= max_hazard))
            {
                seen[e.to] = true;
                q.push(e.to);
            }
        }
    }
    return seen[to];
}


int main()
{
    int N;
    cin >> N;
    vector<adjacency_list> graph(N+1);
    
    int M;
    cin >> M;
    
    int S, E;
    cin >> S >> E;
    
    
    vector<ll> hazards;
    
    for(int i = 0; i < M; i++)
    {
        int from, to;
        ll hazard, length;
        cin >> from >> to >> hazard >> length;
        hazards.push_back(hazard);
        graph[from].push_back(edge(to,hazard, length));
        graph[to].push_back(edge(from,hazard, length));
    }
    
    sort(hazards.begin(), hazards.end());
    auto end_unique = unique(hazards.begin(), hazards.end());
    vector<ll> search_values;
    search_values.push_back((ll)0); // To ensure that there is value too small
    for(auto p = hazards.begin(); p != end_unique; ++p)
    {
        search_values.push_back(*p);
    }
    
    // Binary search
    // low_index can't reach, high_index can reach, stop when adjacent
    int low_index = 0;
    int high_index = (int)search_values.size() - 1;
    while(high_index > low_index + 1)
    {
        int mid_index = (low_index + high_index) / 2;
        ll mid_value = search_values[mid_index];
        if(can_reach(S, E, graph, mid_value))
        {
            high_index = mid_index;
        }
        else
        {
            low_index = mid_index;
        }
    }
    ll minmax = search_values[high_index];
    cout << minmax << endl;
    
    // Min summed total Dijkstra over lengths, subject to hazard constraint
    priority_queue<pair<ll, int> > pql;
    vector<ll> lengths(N + 1, inf);
    pql.push(make_pair((ll)0, S));
    while(!pql.empty() && (lengths[E] == inf))
    {
        ll length_here = -pql.top().first;
        int here = pql.top().second;
        pql.pop();
        
        if(lengths[here] == inf)
        {
            lengths[here] = length_here;
            int n_adj = (int) graph[here].size();
            for(int i = 0; i < n_adj; i++)
            {
                edge e = graph[here][i];
                if(e.hazard <= minmax)
                {
                    ll possible = length_here + e.length;
                    if(lengths[e.to] > possible)
                    {
                        pql.push(make_pair(-possible, e.to));
                    }
                }
            }
        }
    }
    
    ll total_length = lengths[E];
    cout << total_length << endl;

    
    return 0;
}

    
    
    
    
