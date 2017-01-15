#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5010, KMAX = 15;
typedef int64_t i64;

int N, K;
int V[2][NMAX];
i64 DP[2][NMAX];

int main() {
    assert(freopen("joc13.in", "r", stdin));
    assert(freopen("joc13.out", "w", stdout));

    int i, j, k;

    cin >> N >> K;
    for (i = 0; i < 2; ++i)
        for (j = 1; j <= N; ++j)
            cin >> V[i][j];

    memset(DP, 0x80, sizeof DP);

    for (i = 1; i <= N; ++i) {
        for (j = 0; j < 2; ++j) {
            i64 sum = 0;
            for (k = 0; k < K && i - k >= 1; ++k) {
                sum += V[j][i - k];
                if (i - k == 1 && j == 0)
                    DP[j][i] = max(DP[j][i], sum);
                else if (k > 0)
                    DP[j][i] = max(DP[j][i], sum + DP[j ^ 1][i - k]);
            }
        }
    }

    cout << max(DP[1][N], DP[0][N] + V[1][N]) << '\n';

    return 0;
}
