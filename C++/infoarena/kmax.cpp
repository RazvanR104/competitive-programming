#include <bits/stdc++.h>

using namespace std;

const int NMAX = 310;

int N, K, R;
int fact[NMAX], invfact[NMAX];
int DP[NMAX][NMAX];

void gcd(int &x, int &y, int a, int b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    gcd(x, y, b, a % b);
    int aux = x;
    x = y;
    y = aux - y * (a / b);
}

int Comb(int N, int K) {
    return fact[N] * invfact[K] % R * invfact[N - K] % R;
}

int main() {
    assert(freopen("kmax.in", "r", stdin));
    assert(freopen("kmax.out", "w", stdout));

    int i, j, k;

    cin >> N >> K >> R;

    fact[0] = 1;
    for (i = 1; i <= N; ++i)
        fact[i] = fact[i - 1] * i % R;

    int inv = 0, ins;
    gcd(inv, ins, fact[N], R);
    if (inv < 0)
        inv = inv % R + R;
    invfact[N] = inv;
    for (i = N - 1; i >= 0; --i)
        invfact[i] = invfact[i + 1] * (i + 1) % R;

    DP[0][0] = 1;
    for (i = 0; i < N; ++i)
        for (j = 0; j <= N; ++j) {
            if (DP[i][j] == 0)
                continue;
            for (k = 1; k <= K && j + k <= N; ++k)
                DP[i + 1][j + k] = (DP[i + 1][j + k] + DP[i][j] * Comb(N - j, k)) % R;
        }

    int answer = 0;
    for (i = 1; i <= N; ++i)
        answer = (answer + DP[i][N]) % R;

    cout << answer << '\n';
    return 0;
}
