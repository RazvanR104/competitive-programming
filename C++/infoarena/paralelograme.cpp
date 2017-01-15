#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010;

int N, M;
short GCD[NMAX][NMAX], MOD[NMAX][NMAX];

int gcd(int a, int b) {
    if (GCD[a][b] != -1)
        return GCD[a][b];
    int _a = a, _b = b;
    int r;
    while (b) {
        r = MOD[a][b];
        a = b;
        b = r;
    }
    GCD[_a][_b] = GCD[_b][_a] = a;
    return a;
}

int main() {
    assert(freopen("paralelograme.in", "r", stdin));
    assert(freopen("paralelograme.out", "w", stdout));

    cin >> N >> M;
    int64_t answer = 0;
    int current;
    memset(GCD, -1, sizeof GCD);
    int _N = min(N, M);
    int _M = max(N, M);
    for (int i = 2; i <= max(N, M); ++i)
			for (int j = 1; j <= max(N, M); ++j) {
				MOD[j][i] = MOD[j - 1][i] + 1;
				if (MOD[j][i] >= i)
					MOD[j][i] -= i;
			}
    for (int i = 1; i <= _N; ++i) {
        for (int j = i; j <= _M; ++j) {
            current = (i - 1) * (j - 1) + (i + 1) * (j + 1) - gcd(i, j) - 2;
            if (i <= N && j <= M)
            	answer += int64_t(N - i + 1) * (M - j + 1) * current;
						if (i != j && i <= M && j <= N)
							answer += int64_t(M - i + 1) * (N - j + 1) * current;
        }
    }
    cout << answer << '\n';

    return 0;
}
