#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int NMAX = 100010;
const i64 inf = 0x3f3f3f3f3f3f3f3fLL;

int N, M;
int V[NMAX];
i64 curr, answer;

struct Node {
    i64 left, right, smax, sum;
} T[4 * NMAX];

void Build(int node, int left, int right) {
    if (left == right) {
        T[node].smax = V[left];
        T[node].left = V[left];
        T[node].right = V[left];
        T[node].sum = V[left];
        return;
    }

    int mid = (left + right) / 2;
    Build(node * 2, left, mid);
    Build(node * 2 + 1, mid + 1, right);

    T[node].left = max(T[node * 2].left, T[node * 2].sum + T[node * 2 + 1].left);
    T[node].right = max(T[node * 2 + 1].right, T[node * 2 + 1].sum + T[node * 2].right);
    T[node].sum = T[node * 2].sum + T[node * 2 + 1].sum;
    T[node].smax = max(T[node * 2].smax, max(T[node * 2 + 1].smax, max(T[node].left, max(T[node].right, T[node * 2].right + T[node * 2 + 1].left))));
}

void Query(int node, int left, int right, int from, int to) {
    if (left >= from && right <= to) {
        answer = max(answer, max(T[node].smax, curr + T[node].left));
        curr = max(curr + T[node].sum, T[node].right);
        return;
    }

    if (left >= right)
        return;

    int mid = (left + right) / 2;
    if (from <= mid)
        Query(node * 2, left, mid, from, to);
    if (to > mid)
        Query(node * 2 + 1, mid + 1, right, from, to);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("sequencequery.in", "r", stdin) != NULL);
    assert(freopen("sequencequery.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i)
        scanf("%d", &V[i]);

    Build(1, 1, N);

    while (M--) {
        scanf("%d %d", &i, &j);

        curr = -inf, answer = -inf;
        Query(1, 1, N, i, j);
        cout << answer << '\n';
    }

	return 0;
}
