#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 200010, inf = 0x3f3f3f3f;

int N, Q, nr_l, total;
int value[NMAX], l[NMAX], lLVL[NMAX], lFATH[NMAX], lSZ[NMAX], lW[NMAX], LVL[NMAX], tree[4 * NMAX], tOffset[NMAX], lazy[4 * NMAX];
int initial[NMAX], nxt[NMAX];
bool visited[NMAX];
vector<int> G[NMAX], P[NMAX];
multiset<int, greater<int>> S[NMAX];

void VDFS(int node, int from) {
    value[node] = initial[node];

    for (auto i : G[node]) {
        if (i == from)
            continue;
        VDFS(i, node);
        value[node] += value[i];
    }
}

void DFS(int node) {
    lW[node] = 1;
    int it, lN = -1, _node;

    visited[node] = true;
    for(it = 0; it < (int)G[node].size(); ++it)
    {
        _node = G[node][it];
        if (visited[_node]) continue;

        LVL[_node] = LVL[node] + 1;

        DFS(_node);

        lW[node] += lW[_node];

        if (lN == -1 || lW[lN] < lW[_node])
            lN = _node;
    }

    if (lN == -1)
    {
        l[node] = ++nr_l;
        lSZ[nr_l] = 1;
        P[nr_l].push_back(node);
        return;
    }

    l[node] = l[lN];
    ++lSZ[l[node]];
    P[l[node]].push_back(node);

    for (it = 0; it < (int)G[node].size(); ++it)
    {
        _node = G[node][it];
        if (LVL[_node] < LVL[node] || _node == lN) continue;
        lFATH[l[_node]] = node;
        lLVL[l[_node]] = LVL[node];
    }
}

void UnLazy(int node, int offset) {
    if (lazy[node + offset]) {
        tree[node * 2 + offset] += lazy[node + offset];
        tree[node * 2 + 1 + offset] += lazy[node + offset];
        lazy[node * 2 + offset] += lazy[node + offset];
        lazy[node * 2 + 1 + offset] += lazy[node + offset];
        lazy[node + offset] = 0;
    }
}

void update(int node, int left, int right, int qleft, int qright, int value, int offset) {
    if (left >= qleft && right <= qright) {
        lazy[node + offset] += value;
        tree[node + offset] += value;
        return;
    }

    if (left > right)
        return;

    UnLazy(node, offset);

    int mid = (left + right) / 2;
    if (qleft <= mid)
        update(node * 2, left, mid, qleft, qright, value, offset);
    if (qright > mid)
        update(node * 2 + 1, mid + 1, right, qleft, qright, value, offset);
}

int query(int node, int left, int right, int pos, int offset) {
    if (left == right)
        return tree[node + offset];

    if (left > right)
        return 0;

    UnLazy(node, offset);

    int mid = (left + right) / 2;
    if (pos <= mid)
        return query(node * 2, left, mid, pos, offset);
    return query(node * 2 + 1, mid + 1, right, pos, offset);
}

void build(int node, int left, int right, int index, int offset) {
    if (left == right) {
        tree[node + offset] = value[P[index][left - 1]];
        return;
    }

    int div = (left + right) >> 1;
    build(node * 2, left, div, index, offset);
    build(node * 2 + 1, div + 1, right, index, offset);
}

int main() {
    //ios_base::sync_with_stdio(false);
    freopen("rafaela.in", "r", stdin);
    freopen("rafaela.out", "w", stdout);

    int i, j, x, y;

    scanf("%d %d", &N, &Q);
    for (i = 1; i < N; ++i) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (i = 1; i <= N; ++i) {
        scanf("%d", &initial[i]);
        total += initial[i];
    }

    VDFS(1, -1);
    LVL[1] = 1;
    DFS(1);

    for (i = 1; i <= nr_l; ++i) {
        reverse(P[i].begin(), P[i].end());
        tOffset[i] = tOffset[i - 1] + lSZ[i - 1] * 4;

        build(1, 1, lSZ[i], i, tOffset[i]);

        for (j = 0; j < P[i].size() - 1; ++j) {
            nxt[P[i][j]] = P[i][j + 1];
            for (auto k : G[P[i][j]]) {
                if (k == P[i][j + 1] || LVL[k] < LVL[P[i][j]])
                    continue;
                S[P[i][j]].insert(value[k]);
            }
        }
    }

    scanf("\n");
    while (Q--) {
        char op;
        scanf("%c", &op);
        int val, v, a, b;
        if (op == 'U') {
            scanf("%d %d\n", &val, &v);
            total += val;
            a = 1;
            b = v;
            while (true) {
                if (l[a] == l[b]) {
                    if (LVL[a] > LVL[b])
                        swap(a, b);
                    update(1, 1, lSZ[l[a]], LVL[a] - lLVL[l[a]], LVL[b] - lLVL[l[a]], val, tOffset[l[a]]);
                    break;
                }

                if (lLVL[l[a]] < lLVL[l[b]])
                    swap(a, b);
                update(1, 1, lSZ[l[a]], 1, LVL[a] - lLVL[l[a]], val, tOffset[l[a]]);
                int top = P[l[a]][0];
                a = lFATH[l[a]];
                //if (S[a].count(value[top]))
                    S[a].erase(S[a].find(value[top]));
                value[top] += val;
                S[a].insert(value[top]);
            }
        } else {
            scanf("%d\n", &v);
            int ret = total - query(1, 1, lSZ[l[v]], LVL[v] - lLVL[l[v]], tOffset[l[v]]);

           multiset<int, greater<int>>::iterator it = S[v].begin();
           if (it != S[v].end())
            ret = max(ret, *it);

            if (nxt[v])
                ret = max(ret, query(1, 1, lSZ[l[nxt[v]]], LVL[nxt[v]] - lLVL[l[nxt[v]]], tOffset[l[nxt[v]]]));

            cout << ret << '\n';
        }
    }

    return 0;
}
