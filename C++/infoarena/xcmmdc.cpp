#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010, LG2NMAX = 10;

int N, M, K, Q;
int T[NMAX][NMAX], DP[LG2NMAX][NMAX][NMAX], opt[NMAX];
int64_t answer[NMAX];

int gcd(int x, int y) {
    while (y) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

int lg2(int value) {
    if (opt[value] != -1)
        return opt[value];

    int ret = 0;
    while ((1 << ret) <= value)
        ++ret;
    opt[value] = ret - 1;
    return ret - 1;
}

int Compute(int x, int y, int len) {
    if (x + len - 1 > N || y + len - 1 > M)
        return -1;

    int lgdist = lg2(len);
    return gcd(gcd(DP[lgdist][x][y], DP[lgdist][x + len - (1 << lgdist)][y]), gcd(DP[lgdist][x][y + len - (1 << lgdist)], DP[lgdist][x + len - (1 << lgdist)][y + len - (1 << lgdist)]));
}

int main() {
    assert(freopen("xcmmdc.in", "r", stdin));
    assert(freopen("xcmmdc.out", "w", stdout));

    int i, j, k;

    memset(opt, 0xff, sizeof opt);

    scanf("%d %d %d %d", &N, &M, &K, &Q);
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            scanf("%d", &T[i][j]);
            DP[0][i][j] = T[i][j];
        }

    for (i = 1; (1 << i) <= min(N, M); ++i)
        for (j = 1; j + (1 << i) - 1 <= N; ++j)
            for (k = 1; k + (1 << i) - 1 <= M; ++k)
                DP[i][j][k] = gcd(gcd(DP[i - 1][j][k], DP[i - 1][j + (1 << (i - 1))][k]), gcd(DP[i - 1][j][k + (1 << (i - 1))], DP[i - 1][j + (1 << (i - 1))][k + (1 << (i - 1))]));
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            int lower = 0;
            for (int bit = (1 << LG2NMAX); bit; bit >>= 1)
                if (Compute(i, j, lower + bit) > K)
                    lower += bit;
            ++lower;

            if (Compute(i, j, lower) != K)
                continue;

            int upper = 0;
            for (int bit = (1 << LG2NMAX); bit; bit >>= 1)
                if (Compute(i, j, upper + bit) >= K)
                    upper += bit;

            ++answer[lower];
            --answer[upper + 1];
        }
    }

    for (i = 1; i <= min(N, M); ++i)
        answer[i] += answer[i - 1];

    while (Q--) {
        int L;
        scanf("%d", &L);
        cout << answer[L] << '\n';
    }

    return 0;
}
