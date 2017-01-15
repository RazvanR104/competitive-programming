#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;
typedef int64_t i64;

int N, M;
i64 costs[NMAX], T[NMAX * 4], lazy[NMAX * 4], answer = 1e18;

void UnLazy(int node) {
    if (lazy[node]) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        T[node * 2] += lazy[node];
        T[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void Update(int node, int left, int right, int qleft, int qright, int value) {
    costs[qleft] += value;
    costs[qright + 1] -= value;
    /*if (qleft > qright)
        return;

    if (qleft <= left && qright >= right) {
        lazy[node] += value;
        T[node] += value;
        return;
    }

    if (left >= right)
        return;

    UnLazy(node);

    int mid = (left + right) / 2;
    if (qleft <= mid)
        Update(node * 2, left, mid, qleft, qright, value);
    if (qright > mid)
        Update(node * 2 + 1, mid + 1, right, qleft, qright, value);*/
}

void Compute(int node, int left, int right) {
    if (left == right) {
        costs[left] = costs[left - 1] + T[node];
        answer = min(answer, costs[left]);
        return;
    }

    UnLazy(node);

    int mid = (left + right) / 2;
    Compute(node * 2, left, mid);
    Compute(node * 2 + 1, mid + 1, right);
}

void Go(int value) {
    if (M % 2 == 0) {
        if (M - value + 1 == M / 2 + 1) {
            Update(1, 1, M, value + 1, M, 1);
            int left = M - value - 1;
            Update(1, 1, M, 1, 1, left);
            Update(1, 1, M, 2, value, -1);
        } else if (M - value + 1 < M / 2 + 1) {
            Update(1, 1, M, value + 1, M, 1);
            int rest = M / 2 + 1 - M + value - 1;
            int next = M - value + 1;
            Update(1, 1, M, 1, 1, next);
            Update(1, 1, M, 2, 2 + rest - 2, 1);
            Update(1, 1, M, 2 + rest - 1, value, -1);
        } else {
            Update(1, 1, M, value + 1, value + M / 2, 1);
            Update(1, 1, M, value + M / 2 + 1, M, -1);
            int next = M / 2 - (M - value - M / 2 + 1);
            Update(1, 1, M, 1, 1, next);
            Update(1, 1, M, 2, value, -1);
        }
    } else {
        if (M - value + 1 == M / 2 + 1) {
            Update(1, 1, M, value + 1, M, 1);
            int left = M - value;
            Update(1, 1, M, 1, 1, left);
            Update(1, 1, M, 2, value, -1);
        } else if (M - value + 1 < M / 2 + 1) {
            Update(1, 1, M, value + 1, M, 1);
            int rest = M / 2 + 1 - M + value - 1;
            int next = M - value + 1;
            Update(1, 1, M, 1, 1, next);
            Update(1, 1, M, 2, 2 + rest - 2, 1);
            Update(1, 1, M, 2 + rest, value, -1);
        } else {
            Update(1, 1, M, value + 1, value + M / 2, 1);
            Update(1, 1, M, value + M / 2 + 2, M, -1);
            int next = M / 2 - (M - value - M / 2);
            Update(1, 1, M, 1, 1, next);
            Update(1, 1, M, 2, value, -1);
        }
    }
}

int main() {
    assert(freopen("permutare2.in", "r", stdin));
    assert(freopen("permutare2.out", "w", stdout));

    int i;

    cin >> M >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Go(1);
    for (i = 1; i < N; ++i) {
        int value;
        cin >> value;
        Go(value + 1);

    }

    //Compute(1, 1, M);
    for (i = 1; i <= M; ++i)
        costs[i] += costs[i - 1];

    for (i = 1; i <= M; ++i) {
        costs[i] += costs[i - 1];
        answer = min(answer, costs[i]);
    }

    cout << answer << '\n';
    return 0;
}
