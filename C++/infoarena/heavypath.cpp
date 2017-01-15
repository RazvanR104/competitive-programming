#include <bits/stdc++.h>

using namespace std;

const int minf = 0xffffffff, NMAX = 100010;

int N, M;
int tsize[NMAX], father[NMAX], level[NMAX], chpos, where[NMAX], V[NMAX], pos[NMAX], chain_level[NMAX];
vector<int> chain[NMAX], G[NMAX];

void DFS(int node, int from) {
    tsize[node] = 1;

    for (const int &it: G[node]) {
        if (it == from)
            continue;
        level[it] = level[node] + 1;
        father[it] = node;
        DFS(it, node);
        tsize[node] += tsize[it];
    }

    int maxpos = -1;
    for (const int &it: G[node]) {
        if (it == from)
            continue;
        if (maxpos == -1 || tsize[maxpos] < tsize[it])
            maxpos = it;
    }

    if (maxpos == -1) {
        where[node] = ++chpos;
        chain[chpos].push_back(node);
        pos[node] = chain[chpos].size() - 1;
    } else {
        where[node] = where[maxpos];
        chain[where[node]].push_back(node);
        pos[node] = chain[where[node]].size() - 1;

        for (const int &it: G[node]) {
            if (it == from || it == maxpos)
                continue;
            chain_level[where[it]] = level[it];
        }
    }
}

struct Node {
    int v;
    Node *l, *r;

    Node(int v = 0, Node *l = 0, Node *r = 0):
        v(v),
        l(l),
        r(r) {
    }
} *ST[NMAX], *nil;

void Update(Node *curr, int left, int right, int pos, int value) {
    if (left == right) {
        curr->v = value;
        return;
    }
    int mid = (left + right) >> 1;
    if (pos <= mid)
        Update(curr->l, left, mid, pos, value);
    else
        Update(curr->r, mid + 1, right, pos, value);
    curr->v = max(curr->l->v, curr->r->v);
}

int Query(Node *curr, int left, int right, int qleft, int qright) {
    if (left >= qleft && right <= qright)
        return curr->v;
    if (left >= right)
        return minf;
    int mid = (left + right) >> 1, ret = minf;
    if (qleft <= mid)
        ret = max(ret, Query(curr->l, left, mid, qleft, qright));
    if (qright > mid)
        ret = max(ret, Query(curr->r, mid + 1, right, qleft, qright));
    return ret;
}

Node *Build(int left, int right, int ch) {
    if (left == right)
        return new Node(V[chain[ch][left]], nil, nil);
    int mid = (left + right) >> 1;
    Node *l = Build(left, mid, ch);
    Node *r = Build(mid + 1, right, ch);
    return new Node(max(l->v, r->v), l, r);
}

int main() {
    assert(freopen("heavypath.in", "r", stdin));
    assert(freopen("heavypath.out", "w", stdout));

    int i;
    int x, y;

    nil = new Node(minf);
    nil->l = nil->r = nil;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i)
        scanf("%d", &V[i]);
    for (i = 1; i < N; ++i) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(1, -1);
    for (i = 1; i <= chpos; ++i)
        ST[i] = Build(0, chain[i].size() - 1, i);
    ST[0] = nil;

    while (M--) {
        int type;
        scanf("%d %d %d", &type, &x, &y);
        if (type == 0)
            Update(ST[where[x]], 0, chain[where[x]].size() - 1, pos[x], y);
        else {
            int answer = minf;
            if (level[x] < level[y])
                swap(x, y);

            if (where[x] == where[y]) {
                answer = max(answer, Query(ST[where[x]], 0, chain[where[x]].size() - 1, pos[x], pos[y]));
                goto PrintAnswer;
            }

            while (where[x] != where[y]) {
                if (chain_level[where[x]] < chain_level[where[y]])
                    swap(x, y);

                answer = max(answer, Query(ST[where[x]], 0, chain[where[x]].size() - 1, pos[x], chain[where[x]].size() - 1));
                x = father[chain[where[x]].back()];
            }

            if (level[x] < level[y])
                swap(x, y);

            if (where[x] == where[y]) {
                answer = max(answer, Query(ST[where[x]], 0, chain[where[x]].size() - 1, pos[x], pos[y]));
                goto PrintAnswer;
            }

            PrintAnswer: cout << answer << '\n';
        }
    }

    return 0;
}
