#include <bits/stdc++.h>

using namespace std;

const int NMAX = 60, MOD = 29989;

int N, P;
int S[NMAX][NMAX], fact[NMAX], invfact[NMAX];

int Expo(int base, int expo) {
    int ret = 1;
    while (expo) {
        if (expo & 1)
            ret = ret * base % MOD;
        expo >>= 1;
        base = base * base % MOD;
    }
    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("frunze.in", "r", stdin) != NULL);
    assert(freopen("frunze.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> N >> P;
    S[0][0] = S[1][1] = 1;
    for (i = 2; i <= N; ++i)
        for (j = 1; j <= i; ++j)
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % MOD;

    int answer = S[N - 2][N - P];

    for (i = P + 1; i <= N; ++i)
        answer = answer * i % MOD;

/*    fact[0] = 1;
    for (i = 1; i <= N; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[N] = Expo(fact[N], MOD - 2);
    for (i = N - 1; i >= 0; --i)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;

    answer = answer * fact[N] % MOD * invfact[P] % MOD * invfact[N - P] % MOD;
*/
    cout << answer << '\n';
	return 0;
}
