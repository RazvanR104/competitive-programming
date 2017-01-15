#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, MOD = 1114111;

int N;
int P[NMAX], DP[NMAX];

int main() {
    assert(freopen("echival2.in", "r", stdin));
    assert(freopen("echival2.out", "w", stdout));

    int i, j;

    cin >> N;
    int pos = 0;
    for (i = 1; i <= (N + 1) / 2; ++i) {
        P[++pos] = i * (3 * i - 1) / 2;
        P[++pos] = -i * (-3 * i - 1) / 2;
    }

    DP[0] = 1;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= pos && i >= P[j]; ++j) {
            if (j % 4 == 1 || j % 4 == 2) {
                DP[i] += DP[i - P[j]];
                if (DP[i] >= MOD)
                    DP[i] -= MOD;
            } else {
                DP[i] -= DP[i - P[j]];
                if (DP[i] < 0)
                    DP[i] += MOD;
            }
        }
    }

    int answer = DP[N] - DP[N - 1];
    if (answer < 0)
        answer += MOD;

    cout << answer << '\n';
    return 0;
}
