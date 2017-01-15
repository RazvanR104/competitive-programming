#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010;

int N, M, nrp;
int father[NMAX], level[NMAX], subtree[NMAX], where[NMAX], pfather[NMAX], offset[NMAX], pos[NMAX], length[NMAX];
int S[4 * NMAX];
vector<int> T[NMAX];

void DFS(int node, int from, int curr_level) {
    level[node] = curr_level;
    subtree[node] = 1;

    int maxnode = -1;
    for (const int &it: T[node]) {
        if (it == from)
            continue;
        father[node] = it;
        DFS(it, node, curr_level + 1);
        subtree[node] += subtree[it];

        if (maxnode == -1 || subtree[it] > subtree[maxnode])
            maxnode = it;
    }

    if (maxnode != -1) {
        pos[node] = ++length[where[maxnode]];
        where[node] = where[maxnode];

        for (const int &it: T[node]) {
            if (it == from || it == maxnode)
                continue;
            pfather[where[it]] = node;
        }
    } else {
        ++nrp;
        pos[node] = ++length[nrp];
        where[node] = nrp;
    }
}

void Update(int node, int left, int right, int pos, int node_update, int offset) {
    if (left == right) {
        if (S[node + offset] == 0)
            S[node + offset] = node_update;
        else S[node + offset] = 0;
        return;
    }

    if (left >= right)
        return;

    int mid = (left + right) >> 1;
    if (pos <= mid)
        Update(node * 2, left, mid, pos, node_update, offset);
    else
        Update(node * 2 + 1, mid + 1, right, pos, node_update, offset);

    int left_value = S[node * 2 + offset];
    int right_value = S[node * 2 + 1 + offset];
    if (level[left_value] <= level[right_value])
        S[node + offset] = left_value;
    else
        S[node + offset] = right_value;
}

int Query(int node, int left, int right, int qleft, int qright, int offset) {
    if (qleft <= left && qright >= right)
        return S[node + offset];

    if (left >= right)
        return 0;

    int mid = (left + right) >> 1;
    int left_value = 0, right_value = 0;

    if (qleft <= mid)
        left_value = Query(node * 2, left, mid, qleft, qright, offset);
    if (qright > mid)
        right_value = Query(node * 2 + 1, mid + 1, right, qleft, qright, offset);

    if (level[left_value] <= level[right_value])
        return left_value;
    return right_value;
}

int main() {
    assert(freopen("confuzie.in", "r", stdin));
    assert(freopen("confuzie.out", "w", stdout));

    int i, j, x, y;

    scanf("%d %d", &N, &M);
    for (i = 1; i < N; ++i) {
        scanf("%d %d", &x, &y);
        T[x].push_back(y);
        T[y].push_back(x);
    }

    level[0] = 1e9;
    DFS(1, -1, 0);

    for (i = 2; i <= nrp; ++i) {
        offset[i] += offset[i - 1];
        offset[i] += length[i - 1] * 4;
    }

    while (M--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d", &x);
            Update(1, 1, length[where[x]], pos[x], x, offset[where[x]]);
            continue;
        }

        scanf("%d %d", &x, &y);
        if (level[x] < level[y])
            swap(x, y);

        int res = 0;
        if (where[x] != where[y]) {
            res = Query(1, 1, length[where[x]], pos[x], length[where[x]], offset[where[x]]);
            x = pfather[where[x]];

        }

        while (where[x] != where[y]) {
            int curr = Query(1, 1, length[where[x]], pos[x], length[where[x]], offset[where[x]]);
            if (curr)
                res = curr;
            x = pfather[where[x]];
        }

        int curr = Query(1, 1, length[where[x]], pos[x], pos[y], offset[where[x]]);
        if (curr)
            res = curr;

        if (res == 0)
            cout << "-1\n";
        else cout << res << '\n';
    }

    return 0;
}
