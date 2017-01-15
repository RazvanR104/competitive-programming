#include <bits/stdc++.h>

using namespace std;

const int NMAX = 16010;

int N, M, pos;
int euler[2 * NMAX], first[NMAX], last[NMAX], level[NMAX], father[NMAX], sons[NMAX];
int nodes[NMAX], answer[NMAX];
int ST[8 * NMAX][2];
vector<int> T[NMAX];

void Merge(int &node, int &left, int &right, int dir) {
    if (left == 0 && right == 0)
        node = 0;
    else if (left == 0)
        node = right;
    else if (right == 0)
        node = left;
    else {
        if (dir == 0)
            node = left;
        else node = right;
    }
}

void Update(int node, int left, int right, int pos, int value) {
    if (left == right) {
        ST[node][0] = ST[node][1] = value;
        return;
    }

    int mid = (left + right) >> 1;
    if (pos <= mid)
        Update(node * 2, left, mid, pos, value);
    else
        Update(node * 2 + 1, mid + 1, right, pos, value);

    Merge(ST[node][0], ST[node * 2][0], ST[node * 2 + 1][0], 0);
    Merge(ST[node][1], ST[node * 2][1], ST[node * 2 + 1][1], 1);
}

int Query(int node, int left, int right, int qleft, int qright, int dir) {
    if (left >= qleft && right <= qright)
        return ST[node][dir];

    int mid = (left + right) >> 1;
    int lt = 0, rt = 0, ret = 0;

    if (qleft <= mid)
        lt = Query(node * 2, left, mid, qleft, qright, dir);
    if (qright > mid)
        rt = Query(node * 2 + 1, mid + 1, right, qleft, qright, dir);

    Merge(ret, lt, rt, dir);
    return ret;
}

void DFS(int node, int curr_level) {
    euler[++pos] = node;
    first[node] = pos;
    level[node] = curr_level;

    for (const int &it: T[node])
        if (level[it] == 0) {
            father[it] = node;
            DFS(it, curr_level + 1);
        }

    euler[++pos] = node;
    last[node] = pos;

    if (T[node].size() == 0) {
        Update(1, 1, 2 * N, first[node], node);
        Update(1, 1, 2 * N, last[node], node);
    }
}

struct Omida {
    int pos, node;
    char dir;

    bool operator>(const Omida &rhs) const {
        return level[node] > level[rhs.node];
    }
} O[NMAX];

int main() {
    assert(freopen("omizi.in", "r", stdin));
    assert(freopen("omizi.out", "w", stdout));

    int i, j;

    cin >> N >> M;
    for (i = 1; i <= N; ++i) {
        int value;
        cin >> value;
        while (value) {
            T[i].push_back(value);
            ++sons[i];
            cin >> value;
        }
    }

    for (i = 1; i <= M; ++i) {
        O[i].pos = i;
        cin >> O[i].node >> O[i].dir;
        nodes[O[i].node] = i;
    }

    DFS(1, 0);
    sort(O + 1, O + M + 1, greater<Omida>());

    for (i = 1; i <= M; ++i) {
        int pos = O[i].pos;
        int node = O[i].node;
        int dir = (O[i].dir == 'D');

        int go = Query(1, 1, 2 * N, first[node], last[node], dir);
        Update(1, 1, 2 * N, first[go], 0);
        Update(1, 1, 2 * N, last[go], 0);

        --sons[father[go]];
        if (sons[father[go]] == 0) {
            Update(1, 1, 2 * N, first[father[go]], father[go]);
            Update(1, 1, 2 * N, last[father[go]], father[go]);
        }

        answer[pos] = go;
    }

    for (i = 1; i <= M; ++i)
        cout << answer[i] << '\n';

    return 0;
}
