#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int N, X, Y, Z;
int sub[NMAX], cnt1[2 * NMAX], cnt2[2 * NMAX];
vector<int> T[NMAX];

void DFS1(int node, int from) {
    sub[node] = 1;
    for (const int &next: T[node]) {
        if (next == from)
            continue;
        DFS1(next, node);
        sub[node] += sub[next];
    }
    ++cnt1[sub[node]];
}

int DFS2(int node, int from) {
    if (sub[node] == X) {
        if (cnt1[Y])
            return 1;
        if (cnt2[Y + sub[node]])
            return 1;
        if (cnt1[Z])
            return 1;
        if (cnt2[Z + sub[node]])
            return 1;
    }

    if (sub[node] == Y) {
        if (cnt1[X])
            return 1;
        if (cnt2[X + sub[node]])
            return 1;
        if (cnt1[Z])
            return 1;
        if (cnt2[Z + sub[node]])
            return 1;
    }

    if (sub[node] == Z) {
        if (cnt1[X])
            return 1;
        if (cnt2[X + sub[node]])
            return 1;
        if (cnt1[Y])
            return 1;
        if (cnt2[Y + sub[node]])
            return 1;
    }

    --cnt1[sub[node]];
    ++cnt2[sub[node]];

    for (const int &next: T[node]) {
        if (next == from)
            continue;
        int ret = DFS2(next, node);
        if (ret)
            return 1;
    }

    ++cnt1[sub[node]];
    --cnt2[sub[node]];
    return 0;
}

int Solve() {
    int i, x, y;

    scanf("%d %d %d %d", &N, &X, &Y, &Z);
    for (i = 1; i < N; ++i) {
        scanf("%d %d", &x, &y);
        T[x].push_back(y);
        T[y].push_back(x);
    }

    DFS1(1, -1);

    int ret = DFS2(1, -1);

    for (i = 1; i <= N; ++i)
        T[i].clear();
    memset(sub, 0, sizeof(sub));
    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));

    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("arbxyz.in", "r", stdin) != NULL);
    assert(freopen("arbxyz.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int T;
    for (scanf("%d", &T); T; --T)
        cout << Solve() << '\n';

	return 0;
}
