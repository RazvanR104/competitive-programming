#include <bits/stdc++.h>

using namespace std;

const int MOD = 666013;
const int NMAX = 1e5 + 10;
typedef int64_t i64;

i64 K, X, N;
int fact[NMAX], invfact[NMAX];

int FastExpo(int base, i64 expo) {
    int answer = 1;
    while (expo) {
        if (expo & 1)
            answer = 1ll * answer * base % MOD;
        expo >>= 1;
        base = 1ll * base * base % MOD;
    }
    return answer;
}

int Comb(int N, int K) {
    return 1ll * fact[N] * invfact[N - K] * invfact[K] % MOD;
}

int main() {
    assert(freopen("xnumere.in", "r", stdin));
    assert(freopen("xnumere.out", "w", stdout));

    int i;

    cin >> K >> X >> N;
    fact[0] = 1;
    for (i = 1; i <= X; ++i)
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    invfact[X] = FastExpo(fact[X], MOD - 2);
    for (i = X - 1; i >= 0; --i)
        invfact[i] = 1ll * invfact[i + 1] * (i + 1) % MOD;

    // A(K, X)
    int A = 1;
    for (i64 it = K - X + 1; it <= K; ++it)
        A = 1ll * A * (it % MOD) % MOD;

    // S(N, X)
    int S = 0;
    for (i = 0; i < X; ++i) {
        int curr = (i & 1) ? (-1) : (1);
        curr *= Comb(X, i);
        curr = 1ll * curr * FastExpo(X - i, N) % MOD;
        S += curr;
        if (S >= MOD)
            S -= MOD;
        if (S < 0)
            S += MOD;
    }
    S = 1ll * S * invfact[X] % MOD;

    cout << 1ll * S * A % MOD << '\n';
    return 0;
}
