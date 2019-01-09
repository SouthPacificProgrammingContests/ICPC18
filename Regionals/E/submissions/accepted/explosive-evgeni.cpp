#include <bits/stdc++.h>
using namespace std;

#define len(x)  (int((x).size()))
#define append push_back
#define ff(a, b)    for (int a = 0; a < int(b); ++a)
#define kk(n)    ff(k, n)
#define ii(n)    ff(i, n)
#define fff(a, b, c) for (int a = int(b); a < int(c); ++a)
#define kkk(a, b) fff(k, a, b)
#define iii(a, b) fff(i, a, b)
#define bb begin()
#define ee end()
#define all(x)  (x).bb, (x).ee

using LL = long long;


const int INFint = 0x7f7f7f7f;  //Works with memset(..).

struct xy {
    int x, y;
    xy() : x(0), y(0) { }
    xy(int _x, int _y) : x(_x), y(_y) { }
};

xy operator-(const xy a, const xy b) { return xy(a.x-b.x, a.y-b.y); }
LL operator^(const xy a, const xy b) { return LL(a.x)*b.y - LL(b.x)*a.y; }
LL operator*(const xy a, const xy b) { return LL(a.x)*b.x + LL(a.y)*b.y; }

struct wire {
    int k;
    vector<xy> pts;

    wire() : k(-INFint), pts() { }

    xy lastpt() {
        return pts[len(pts)-1];
    }
};

bool operator<(const wire &a, const wire &b) {
    return a.pts[0].x < b.pts[0].x;
}

vector<wire> wires;
vector<vector<int> > adjmat;

bool strands(xy a, xy b, xy p, xy q) {
    xy ba = b - a;
    LL pside = ba ^ (p - a);
    LL qside = ba ^ (q - a);
    if (0 == pside
    ||  0 == qside
    ||  pside < 0 && 0 < qside
    ||  qside < 0 && 0 < pside)
        return true;
    return false;
}

bool doTheyIntersect(xy a, xy b, xy p, xy q) {
    if (strands(a, b, p, q)
    &&  strands(p, q, a, b)) {
        if (((b - a) ^ (q - p)) == 0) {  // Parallel. Therefore collinear.
            if ((b - a)*(p - a) < 0
            &&  (b - a)*(q - a) < 0
            ||  (a - b)*(p - b) < 0
            &&  (a - b)*(q - b) < 0)  // Non-overlapping collinear.
                return false;
        }
        return true;
    }
    return false;
}

bool doesItIntersect(wire &a, wire &b) {
    ii (len(a.pts)-1)
    kk (len(b.pts)-1) {
        if (doTheyIntersect(a.pts[i], a.pts[i+1],
                            b.pts[k], b.pts[k+1]))
            return true;
    }
    return false;
}

int subsolve(int a, int b);
int dp(vector<int> &selected, int from, vector<int> &memo, vector<int> &nexts) {
    if (from >= len(selected)-1)
        return 0;

    if (-1 != memo[from])
        return memo[from];

    int highest = dp(selected, from+1, memo, nexts);

    iii (from+1, len(selected))
    if (adjmat[selected[from]][selected[i]]) {
        int here = wires[selected[from]].k
                 + wires[selected[i]].k
                 + subsolve(selected[from], selected[i])
                 + dp(selected, max(nexts[from], nexts[i]), memo, nexts);
        highest = max(highest, here);
    }

    return memo[from] = highest;
}

vector<int> makeNexts(vector<int> &selected) {
    vector<int> nexts(len(selected), INFint);
    ii (len(selected))
    kkk (i+1, len(selected)) {
        if (wires[selected[k]].pts[0].x
        >   wires[selected[i]].lastpt().x) {
            nexts[i] = k;
            break;
        }
    }
    return nexts;
}

vector<vector<int> > subsolve_dp;
int subsolve(int a, int b) {
    int &rr = subsolve_dp[a][b];
    if (-1 != rr)
        return rr;

    vector<int> selected;
    ii (len(wires))
    if (!adjmat[a][i] && !adjmat[b][i]) {
        if (wires[a].pts[0].x
        <   wires[i].pts[0].x
        &&  wires[i].lastpt().x
        <   max(wires[a].lastpt().x,
                wires[b].lastpt().x)) {
            
            selected.append(i);
        }
    }

    vector<int> memo(len(selected), -1);
    vector<int> nexts = makeNexts(selected);
    return rr = dp(selected, 0, memo, nexts);
}


int main() {
    int N;
    cin >> N;
    wires.resize(N);
    adjmat.resize(N, vector<int>(N, 0));
    subsolve_dp.resize(N, vector<int>(N, -1));

    ii (N) {
        int p;
        cin >> wires[i].k >> p;
        wires[i].pts.resize(p);
        kk (p)
            cin >> wires[i].pts[k].x
                >> wires[i].pts[k].y;
    }
    sort(all(wires));

    ii (N)
    kk (i) {
        adjmat[i][k] = adjmat[k][i] = doesItIntersect(wires[i], wires[k]);
    }

    vector<int> full(N);
    ii (N)
        full[i] = i;

    vector<int> memo(N, -1);
    vector<int> full_nexts = makeNexts(full);
    int highest = dp(full, 0, memo, full_nexts);

    cout << highest << '\n';
    

    return 0;
}