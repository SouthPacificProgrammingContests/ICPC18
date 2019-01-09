//
//  hazardous_sol1.cpp
//
//  Problem setter's code for "Hazardous Driving" for South Pacific round of ICPC
//
//  Based on 2 priority queue Dijkstra's implementations, first a min-max
//  over hazard ratings, then a standard sum of lengths subject to hazard
//  constraint
//

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll inf = (ll)200000 * (ll)2000000000;

struct edge
{
    int to;
    ll hazard;
    ll length;
    
    edge(int t, ll h, ll l) : to(t), hazard(h), length(l) {}
};
typedef vector<edge> adjacency_list;


int main()
{
    int N;
    cin >> N;
    vector<adjacency_list> graph(N+1);
    
    int M;
    cin >> M;
    
    int S, E;
    cin >> S >> E;
    
    
    for(int i = 0; i < M; i++)
    {
        int from, to;
        ll hazard, length;
        cin >> from >> to >> hazard >> length;
        graph[from].push_back(edge(to,hazard, length));
        graph[to].push_back(edge(from,hazard, length));
    }
    
    ll minmax = inf;

    // Min max Dijkstra over hazards
    priority_queue<pair<ll, int> > pqh;
    vector<ll> hazards(N + 1, inf);
    pqh.push(make_pair((ll)0, S));
    while(!pqh.empty() && (hazards[E] == inf))
    {
        ll hazard_here = -pqh.top().first;
        int here = pqh.top().second;
        pqh.pop();
        
        if(hazards[here] == inf)
        {
            hazards[here] = hazard_here;
            int n_adj = (int) graph[here].size();
            for(int i = 0; i < n_adj; i++)
            {
                edge e = graph[here][i];
                ll possible = max(hazard_here, e.hazard);
                if(hazards[e.to] > possible)
                {
                    pqh.push(make_pair(-possible, e.to));
                }
            }
        }
    }
    minmax = hazards[E];
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
