#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int NMAX = 1000010, MMAX = 2100;
const i64 inf = 0x3f3f3f3f3f3f3f3fLL, minf = 0xc0c0c0c0c0c0c0c0LL;

int N, K, M;
int res;

i64 V[NMAX], A[MMAX], B[MMAX];
i64 Max[4 * NMAX], Min[4 * NMAX];
i64 curr_min, curr_max;
i64 now;

void Build(int node, int left, int right) {
    if (left == right)
        Max[node] = Min[node] = V[left];

    if (left >= right)
        return;

    int mid = (left + right) / 2;
    Build(node * 2, left, mid);
    Build(node * 2 + 1, mid + 1, right);

    Max[node] = max(Max[node * 2], Max[node * 2 + 1]);
    Min[node] = min(Min[node * 2], Min[node * 2 + 1]);
}

void Query(int node, int left, int right, int qleft, int qright) {
    if (left >= qleft && right <= qright) {
        i64 new_max = max(curr_max, Max[node]);
        i64 new_min = min(curr_min, Min[node]);

        if ((new_max - new_min + 1) / 2 <= now) {
            curr_max = new_max;
            curr_min = new_min;
            res = right;
            return;
        }
    }

    if (left >= right)
        return;

    int mid = (left + right) / 2;
    if (qleft <= mid && (res == left - 1 || res == -1))
        Query(node * 2, left, mid, qleft, qright);
    if (qright > mid && (res == mid || res == -1))
        Query(node * 2 + 1, mid + 1, right, qleft, qright);
}

int Check(i64 val) {
    int ret = 0;
    now = val;
    for (int i = 1; i <= N; ) {
        curr_min = inf;
        curr_max = minf;
        res = -1;
        Query(1, 1, N, i, N);
        i = res + 1;
        ++ret;

        if (ret > K)
            return ret;
    }
    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("ksecv4.in", "r", stdin) != NULL);
    assert(freopen("ksecv4.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    //memset(Min, inf, sizeof(Min));
    //memset(Max, minf, sizeof(Max));

    cin >> N >> K >> M;
    for (i = 0; i < M; ++i)
        cin >> A[i];
    for (i = 0; i < M; ++i)
        cin >> B[i];

    for (i = 1; i <= N; ++i)
        V[i] = (A[(i - 1) % M] ^ B[(i - 1) / M]);

    Build(1, 1, N);

    i64 answer = (1LL << 60) - 1;
    for (i64 bit = (1LL << 59); bit; bit >>= 1) {
        if (Check(answer - bit) <= K)
            answer -= bit;
    }

    cout << answer << '\n';
	return 0;
}
