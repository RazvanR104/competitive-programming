#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010;
typedef int64_t i64;

int N, K;
int A[NMAX], B[NMAX];

int main() {
    assert(freopen("tarabe.in", "r", stdin));
    assert(freopen("tarabe.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &K);
    for (i = 1; i <= N; ++i)
        scanf("%d %d", &B[i], &A[i]);

    i64 left = 1, right = 1000499500000LL, mid;
    i64 res = -1, res_mid = -1, res_cnt = -1;
    while (left <= right) {
        mid = (left + right) >> 1;

        i64 cnt = 0;
        i64 sum = 0;
        for (i = 1; i <= N; ++i) {
            i64 now = (mid - A[i]) / B[i] + 1;
            if (mid - A[i] >= 0) {
                cnt += now;
                sum += 1ll * now * A[i] + 1ll * now * (now - 1) / 2 * B[i];
            }
        }

        if (cnt >= K) {
            res = sum;
            res_cnt = cnt;
            res_mid = mid;
            right = mid - 1;
        } else
            left = mid + 1;
    }

    if (res_cnt > K)
        res -= (res_cnt - K) * res_mid;

    cout << res << '\n';
    return 0;
}
