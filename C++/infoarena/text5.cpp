#include <bits/stdc++.h>

using namespace std;

const int LMAX = 1e6 + 10, VMAX = 1010, minf = 0x8f8f8f8f;

int N;
int last[2][3][VMAX];
int DP[2][LMAX], jump[2][LMAX];
char str[LMAX];

int Jump(int pos, int type) {
    if (jump[type][pos])
        return jump[type][pos];

    int _last;
    if (type == 0) {
        _last = last[0][pos % 2][str[pos] * 10 + str[pos + 1]];
        if (_last + 2 >= N || _last == pos) {
            jump[0][pos] = _last + 2;
            return jump[0][pos];
        }
    } else {
        _last = last[1][pos % 3][str[pos] * 100 + str[pos + 1] * 10 + str[pos + 2]];
        if (_last + 3 >= N || _last == pos) {
            jump[1][pos] = _last + 3;
            return jump[1][pos];
        }
    }

    int now = pos + (type == 0 ? 2 : 3);
    while (now <= _last)
        now = Jump(now, type);

    jump[type][pos] = now;
    return jump[type][pos];
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("text5.in", "r", stdin) != NULL);
    assert(freopen("text5.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> N >> (str + 1);

    int i;

    for (i = 1; i <= N; ++i)
        str[i] -= '0';

    for (i = 1; i <= N; ++i) {
        if (i + 1 <= N) {
            int r = i % 2;
            last[0][r][str[i] * 10 + str[i + 1]] = i;
        }
        if (i + 2 <= N) {
            int r = i % 3;
            last[1][r][str[i] * 100 + str[i + 1] * 10 + str[i + 2]] = i;
        }
    }

    memset(DP, minf, sizeof(DP));
    DP[0][N + 1] = DP[1][N + 1] = 0;
    for (i = N - 1; i >= 1; --i) {
        int _jump = Jump(i, 0);
        int __jump = Jump(i, 1);
        DP[0][i] = max(DP[0][_jump], DP[1][_jump]) + 1;
        DP[1][i] = max(DP[0][__jump], DP[1][__jump]) + 1;
    }

    cout << max(DP[0][1], DP[1][1]) << '\n';

    for (i = 1; i <= N; ) {
        if (DP[0][i] >= DP[1][i]) {
            cout << i << " 2\n";
            i = Jump(i, 0);
        } else {
            cout << i << " 3\n";
            i = Jump(i, 1);
        }
    }

	return 0;
}
