#include <bits/stdc++.h>

using namespace std;

const int FMAX = 30010, NMAX = 500010;

int N, M, F, DX, DY, where[4 * NMAX];
int64_t T[4 * NMAX], lazy[4 * NMAX];

struct Rectangle {
    int x1, x2, y1, y2, c;
} R[FMAX];

struct Event {
    int type, pos;
    Event(int type = 0, int pos = 0) : type(type), pos(pos) {}
};
vector<Event> E[NMAX];

void BuildTree(int node, int left, int right) {
    if (left == right) {
        where[node] = left;
        return;
    }

    int mid = (left + right) / 2;
    BuildTree(node * 2, left, mid);
    BuildTree(node * 2 + 1, mid + 1, right);

    where[node] = where[node * 2];
}

void Update(int node, int left, int right, int from, int to, int val) {
    if (left >= from && right <= to) {
        T[node] += val;
        lazy[node] += val;
        return;
    }

    if (left >= right)
        return;

    T[node * 2] += lazy[node];
    T[node * 2 + 1] += lazy[node];
    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1]  += lazy[node];
    lazy[node] = 0;

    int mid = (left + right) / 2;
    if (from <= mid)
        Update(node * 2, left, mid, from, to, val);
    if (to > mid)
        Update(node * 2 + 1, mid + 1, right, from, to, val);

    if (T[node * 2] <= T[node * 2 + 1]) {
        T[node] = T[node * 2];
        where[node] = where[node * 2];
    } else {
        T[node] = T[node * 2 + 1];
        where[node] = where[node * 2 + 1];
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("demolish.in", "r", stdin) != NULL);
    assert(freopen("demolish.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> N >> M >> F >> DX >> DY;

    int i;
    for (i = 1; i <= F; ++i)
        cin >> R[i].x1 >> R[i].y1 >> R[i].x2 >> R[i].y2 >> R[i].c;

    BuildTree(1, 0, M - DY);

    for (i = 1; i <= F; ++i) {
        E[R[i].x1 + 1].push_back(Event(1, i));
        if (R[i].x2 + DX <= N)
            E[R[i].x2 + DX].push_back(Event(-1, i));
    }

    int64_t answer = 1LL << 62;
    int ax1 = -1, ay1 = -1;

    for (i = 0; i <= N; ++i) {
        for (const auto &it : E[i])
            Update(1, 0, M - DY, max(0, R[it.pos].y1 - DY + 1), R[it.pos].y2 - 1, it.type * R[it.pos].c);

        if (i >= DX && answer > T[1]) {
            answer = T[1];
            ax1 = i;
            ay1 = where[1];
        }
    }

    cout << answer << '\n';
    cout << ax1 - DX << ' ' << ay1 << ' ' << ax1 << ' ' << ay1 + DY << '\n';
	return 0;
}
