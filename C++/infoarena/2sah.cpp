#include <bits/stdc++.h>

using namespace std;

const int MMAX = 4, MOD = 100003;

struct Matrix {
    int M[MMAX][MMAX];

    Matrix() {
        memset(M, 0, MMAX * MMAX * sizeof(int));
    }

    void Unitate() {
        for (int i = 1; i < MMAX; ++i)
            M[i][i] = 1;
    }

    Matrix operator*(const Matrix &rhs) {
        Matrix ret = Matrix();
        for (int i = 1; i < MMAX; ++i) {
            for (int j = 1; j < MMAX; ++j) {
                for (int k = 1; k < MMAX; ++k) {
                    ret.M[i][k] += 1ll * M[i][j] * rhs.M[j][k] % MOD;
                }
            }
        }
        return ret;
    }
};

int T, N, K;

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("2sah.in", "r", stdin) != NULL);
    assert(freopen("2sah.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> T >> N >> K;

    if (T == 1) {
        int answer = 1, base = 3;
        --K;
        while (K) {
            if (K & 1)
                answer = 1ll * answer * base % MOD;
            base = 1ll * base * base % MOD;
            K >>= 1;
        }
        cout << answer << '\n';
        return 0;
    }

    int pos = N - K + 2;

    if (pos == 1 || pos == 2) {
        cout << 1 << '\n';
        return 0;
    } else if (pos == 3) {
        cout << 2 << '\n';
        return 0;
    }

    int expo = pos - 3;

    Matrix answer = Matrix();
    answer.Unitate();
    Matrix base = Matrix();
    base.M[1][3] = base.M[2][1] = base.M[2][3] = base.M[3][2] = base.M[3][3] = 1;

    while (expo) {
        if (expo & 1)
            answer = answer * base;
        base = base * base;
        expo >>= 1;
    }

    cout << (answer.M[1][3] + answer.M[2][3] + 1ll * 2 * answer.M[3][3] % MOD) % MOD << '\n';
	return 0;
}
