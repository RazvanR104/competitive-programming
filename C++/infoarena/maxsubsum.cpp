#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010;
typedef int64_t i64;

int N, M;
int A[NMAX], B[NMAX];
i64 maxA[NMAX], maxB[NMAX];

int main() {
    assert(freopen("maxsubsum.in", "r", stdin));
    assert(freopen("maxsubsum.out", "w", stdout));

    int i, j;

    cin >> N >> M;
    for (i = 1; i <= N; ++i)
        cin >> A[i];
    for (j = 1; j <= M; ++j)
        cin >> B[j];

    for (i = 1; i <= N; ++i) {
        i64 curr = 0;
        for (j = i; j >= 1; --j)
            curr += A[j];
        maxA[i] = curr;
        for (j = i + 1; j <= N; ++j) {
            curr += A[j];
            curr -= A[j - i];
            maxA[i] = max(maxA[i], curr);
        }
    }

    for (i = 1; i <= M; ++i) {
        i64 curr = 0;
        for (j = i; j >= 1; --j)
            curr += B[j];
        maxB[i] = curr;
        for (j = i + 1; j <= M; ++j) {
            curr += B[j];
            curr -= B[j - i];
            maxB[i] = max(maxB[i], curr);
        }
    }

    i64 answer = 0;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            answer = max(answer, 1ll * maxA[i] * j + 1ll * maxB[j] * i);

    cout << answer << '\n';
    return 0;
}
