#include <bits/stdc++.h>
using namespace std;

#define len(x)  (int((x).size()))
#define append push_back
#define ff(a, b)    for (int a = 0; a < int(b); ++a)
#define ii(n)    ff(i, n)


struct an_upgrade {
    char type;
    int depth;
    vector<int> ancestor_pow2n;
    an_upgrade() : type('E'), depth(-1), ancestor_pow2n() { }
};

int goUpTo(int depth, int from, vector<an_upgrade> &tree) {
    int delta = tree[from].depth - depth;
    for (int power = 0; delta >> power; ++power)
        if ((delta >> power) & 1)
            from = tree[from].ancestor_pow2n[power];
    return from;
}


void justUnderLCA(int &u, int &v, vector<an_upgrade> &tree) {
    int left = 0;
    int right = min(tree[u].depth, tree[v].depth) + 1;
    while (right - left >= 2) {
        int mid = (left + right) / 2;
        if (goUpTo(mid, u, tree) == goUpTo(mid, v, tree))
            left = mid;
        else
            right = mid;
    }
    u = goUpTo(right, u, tree);
    v = goUpTo(right, v, tree);
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<an_upgrade> tree(1);
    tree[0].type = 'G';
    tree[0].depth = 0;
    ii (N) {
        an_upgrade u;
        int parent;
        cin >> u.type >> parent;
        u.ancestor_pow2n.append(parent-1);
        u.depth = tree[parent-1].depth + 1;

        for (int n = 0; (2 << n) <= u.depth; ++n) {
            an_upgrade &halfway = tree[u.ancestor_pow2n[n]];
            u.ancestor_pow2n.append(halfway.ancestor_pow2n[n]);
        }
        tree.append(u);
    }

    int result = 0;
    ii (Q) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        if (u == v) {
            ++result;
            continue;
        }
        if (tree[u].depth > tree[v].depth)
            swap(u, v);
        if (tree[u].depth != tree[v].depth) {
            int just_below_v_depth = goUpTo(tree[u].depth+1, v, tree);
            if (tree[just_below_v_depth].ancestor_pow2n[0] == u) {
                if ('L' == tree[just_below_v_depth].type)
                    ++result;
                continue;
            }
        }
        justUnderLCA(u, v, tree);
        if ('L' == tree[min(u, v)].type)
            ++result;
    }

    cout << result << '\n';


    return 0;
}