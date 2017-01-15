#include <bits/stdc++.h>

using namespace std;

const int SMAX = 50010, MOD = 700001;

int S;
int DP[SMAX], P[SMAX];

int main() {
    assert(freopen("crescator2.in", "r", stdin));
    assert(freopen("crescator2.out", "w", stdout));

    int i, j, pos = 0;

    cin >> S;
    /*for (i = 1; i <= (S + 1) / 2; ++i) {
        P[++pos] = i * (3 * i - 1) / 2;
        P[++pos] = (-i) * (-3 * i - 1) / 2;
    }

    int answer = 0;
    DP[0] = 1;
    for (i = 1; i <= S; ++i) {
        for (j = 1; j <= pos && i - P[j] >= 0; ++j) {
            if (j % 4 == 1 || j % 4 == 2)
                DP[i] += DP[i - P[j]];
            else
                DP[i] -= DP[i - P[j]];
            if (DP[i] >= MOD)
                DP[i] -= MOD;
            if (DP[i] < 0)
                DP[i] += MOD;
        }
        answer += DP[i];
        if (answer >= MOD)
            answer -= MOD;
    }*/

    int answer = 0;
    DP[0] = 1;
    for (i = 1; i <= S; ++i) {
        for (j = 0; j <= S - i; ++j) {
            DP[j + i] = (DP[j + i] + DP[j]) % MOD;
        }
    }

    for (i = 1; i <= S; ++i)
        answer = (answer + DP[i]) % MOD;

    cout << answer << '\n';

    return 0;
}
