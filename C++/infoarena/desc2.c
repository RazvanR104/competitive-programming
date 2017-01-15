#include <stdio.h>
#include <string.h>

#define NMAX 10010
#define MOD 10007

int N, K, X;
int DP[NMAX];

void Fix(int *value) {
    if (*value >= MOD)
        *value -= MOD;
}

int main() {
    freopen("desc2.in", "r", stdin);
    freopen("desc2.out", "w", stdout);

    scanf("%d %d %d", &N, &K, &X);

    int line = N - (K - 1) * K / 2 * X - K;

    DP[0] = 1;
    for (int i = 1; i <= K; ++i) {
        for (int j = 0; j + i <= line; ++j) {
            DP[i + j] = DP[i + j] + DP[j];
            Fix(DP + i + j);
        }
    }

    printf("%d\n", DP[line]);

    return 0;
}
