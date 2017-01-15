#include <bits/stdc++.h>

using namespace std;

const int PMAX = 25, MSIZE = 65, MOD = 666013;

typedef unsigned long long i64;

int N, P, T;
int answer[MSIZE], fin[MSIZE];
int base[MSIZE][MSIZE], result[MSIZE][MSIZE], pos[PMAX][3];

#define pos(x, y) (pos[x][y])

void Multiply(int lhs[][MSIZE],  int rhs[][MSIZE]) {
    int i, j, k;
    int temp[MSIZE][MSIZE];
    memset(temp, 0, sizeof(temp));

    for (i = 0; i < MSIZE; ++i)
        for (j = 0; j < MSIZE; ++j) {
            for (k = 0; k < MSIZE; ++k) {
                temp[j][k] = (temp[j][k] + i64(lhs[j][i]) * rhs[i][k]) % MOD;
            }
        }

    memcpy(lhs, temp, sizeof(temp));
}

int main() {
    ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    assert(freopen("ikebana.in", "r", stdin) != NULL);
    assert(freopen("ikebana.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> N >> P >> T;

    for (i = 0; i <= P; ++i)
        for (j = 0; j < 3; ++j)
            pos[i][j] = i * 3 + j;

    answer[pos(0, 2)] = 1;
    answer[pos(P, 0)] = 2;
    answer[pos(P, 1)] = 0;
    answer[pos(P, 2)] = T - 4;

    for (j = 1; j <= P; ++j) {
        base[pos(j - 1, 0)][pos(j, 0)] = 2;
        base[pos(j - 1, 1)][pos(j, 0)] = 1;
        base[pos(j - 1, 2)][pos(j, 0)] = 2;

        base[pos(j - 1, 0)][pos(j, 1)] = 1;

        base[pos(j - 1, 0)][pos(j, 2)] = T - 4;
        base[pos(j - 1, 2)][pos(j, 2)] = T - 4;
    }

    base[pos(P, 0)][pos(P, 0)] = 2;
    base[pos(P, 1)][pos(P, 0)] = 1;
    base[pos(P, 2)][pos(P, 0)] = 2;

    base[pos(P, 0)][pos(P, 1)] = 1;

    base[pos(P, 0)][pos(P, 2)] = T - 4;
    base[pos(P, 2)][pos(P, 2)] = T - 4;

    base[pos(P, 0)][pos(0, 2)] = 1;
    base[pos(P, 2)][pos(0, 2)] = 1;

    for (i = 0; i < MSIZE; ++i)
        result[i][i] = 1;

    int expo = N - 1;
    while (expo) {
        if (expo & 1) {
            Multiply(result, base);
        }
        expo >>= 1;
        Multiply(base, base);
    }

    for (i = 0; i < MSIZE; ++i) {
        for (j = 0; j < MSIZE; ++j) {
            fin[i] = (fin[i] + i64(answer[j]) * result[j][i]) % MOD;
        }
    }

    int final_answer = 0;
    for (i = 0; i <= P; ++i)
        for (j = 0; j < 3; ++j) {
            if (j == 1)
                continue;
            final_answer += fin[pos(i, j)];
            if (final_answer >= MOD)
                final_answer -= MOD;
        }

    cout << final_answer << '\n';

    return 0;
}
