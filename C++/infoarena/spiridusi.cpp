#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, inf = 0x3f3f3f3f;

int N, C, answer = -inf;
int S[NMAX], P[NMAX], T[4 * NMAX], lazy[4 * NMAX];
int st[NMAX], sum[NMAX], stpos;
vector<int> G[NMAX];

void UnLazy(int node) {
    T[node * 2] += lazy[node];
    T[node * 2 + 1] += lazy[node];
    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1] += lazy[node];
    lazy[node] = 0;
}

void Update(int node, int left, int right, int from, int to, int val) {
    if (left >= from && right <= to) {
        T[node] += val;
        lazy[node] += val;
        return;
    }

    if (left >= right)
        return;

    UnLazy(node);

    int mid = (left + right) / 2;
    if (from <= mid)
        Update(node * 2, left, mid, from, to, val);
    if (to > mid)
        Update(node * 2 + 1, mid + 1, right, from, to, val);

    T[node] = max(T[node * 2], T[node * 2 + 1]);
}

int Query(int node, int left, int right, int from, int to) {
    if (left >= from && right <= to)
        return T[node];

    if (left >= right)
        return -inf;

    UnLazy(node);

    int mid = (left + right) / 2, ret = -inf;
    if (from <= mid)
        ret = max(ret, Query(node * 2, left, mid, from, to));
    if (to > mid)
        ret = max(ret, Query(node * 2 + 1, mid + 1, right, from, to));

    return ret;
}

void DFS(int node, int father) {
    st[++stpos] = node;
    sum[stpos] = sum[stpos - 1] + S[node];
    Update(1, 1, N, 1, stpos, P[node]);

    int where = 1;

    for (int bit = (1 << 17); bit; bit >>= 1)
        if (where + bit <= stpos && sum[where + bit] + C < sum[stpos])
            where += bit;
    if (sum[where] + C < sum[stpos])
        ++where;
    if (sum[stpos] - sum[where - 1] > C)
        ++where;

    answer = max(answer, Query(1, 1, N, where, stpos));

    for (const int &it : G[node]) {
        if (it == father)
            continue;
        DFS(it, node);
    }

    Update(1, 1, N, 1, stpos, -P[node]);
    --stpos;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("spiridusi.in", "r", stdin) != NULL);
    assert(freopen("spiridusi.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    scanf("%d %d", &N, &C);
    for (i = 1; i <= N; ++i)
        scanf("%d", &S[i]);
    for (j = 1; j <= N; ++j)
        scanf("%d", &P[j]);

    for (i = 1; i < N; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(1, -1);

    cout << answer << '\n';

	return 0;
}
