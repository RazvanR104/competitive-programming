#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int NMAX = 510, QMAX = 500010;

int N, M, NQ;
int D[NMAX][NMAX], ST[4 * NMAX], res[QMAX];
char L[NMAX][NMAX];

struct Query {
    int l, c, l1, l2, pos;
    bool operator<(const Query &rhs) const {
        return l < rhs.l;
    }
} Q[QMAX];

int Sorted[QMAX];
struct Compare {
    bool operator()(const int &lhs, const int &rhs) const {
        return Q[lhs].l < Q[rhs].l;
    }
};

void Update(int node, int left, int right, int pos, int value) {
    if (left == right) {
        ST[node] = value;
        return;
    }

    if (left > right)
        return;

    int mid = (left + right) >> 1;
    if (pos <= mid)
        Update(node * 2, left, mid, pos, value);
    if (pos > mid)
        Update(node * 2 + 1, mid + 1, right, pos, value);

    ST[node] = max(ST[node * 2], ST[node * 2 + 1]);
}

int Query(int node, int left, int right, int qleft, int qright) {
    if (qleft <= left && qright >= right) {
        return ST[node];
    }

    if (left > right)
        return 0;

    int mid = (left + right) >> 1, res = 0;
    if (qleft <= mid)
        res = max(res, Query(node * 2, left, mid, qleft, qright));
    if (qright > mid)
        res = max(res, Query(node * 2 + 1, mid + 1, right, qleft, qright));

    return res;
}

void Recompute(int L) {
    int i, j;
    for (i = 1; i <= N; ++i) {
        int Max = 0;
        for (j = 1; j <= N; ) {
            if (D[i][j] < L) {
                ++j;
                continue;
            }
            int curr = 1;
            while (D[i][j + 1] >= L) {
                ++curr;
                ++j;
            }
            Max = max(Max, curr);
            ++j;
        }
        Update(1, 1, N, i, Max);
    }
}

int main() {
	//ios_base::sync_with_stdio(false);
	//#ifndef ONLINE_JUDGE
    freopen("lcdr.in", "r", stdin);
    freopen("lcdr.out", "w", stdout);
	//freopen("debug.err", "w", stderr);
    //#endif

    int i, j, k;
    scanf("%d %d %d\n", &N, &M, &NQ);
    for (i = 1; i <= N; ++i)
        gets(L[i] + 1);

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (L[i][j] == '1') {
                int num = 1;
                for (k = i + 1; k <= N && L[k][j] == '1'; ++k)
                    ++num;
                D[i][j] = num;
            }
        }
    }

    for (i = 1; i <= NQ; ++i) {
        scanf("%d %d %d %d", &Q[i].l, &Q[i].c, &Q[i].l1, &Q[i].l2);
        Q[i].pos = i;
        Sorted[i] = i;
    }
    //sort(Sorted + 1, Sorted + NQ + 1, Compare());
    sort(Q + 1, Q + NQ + 1);

    for (i = 1; i <= NQ; ++i) {
        j = i;
        k = i - 1;
        if (Q[j].l != Q[k].l)
            Recompute(Q[j].l);
        int q = Query(1, 1, N, Q[j].l1, Q[j].l2 - Q[j].l + 1);
        res[Q[j].pos] = (q >= Q[j].c);
    }

    for (i = 1; i <= NQ; ++i)
        cout << res[i] << '\n';

	return 0;
}
