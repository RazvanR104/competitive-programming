#include <bits/stdc++.h>

using namespace std;

const int LMAX = 5e6 + 10;

char S[LMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("subbit.in", "r", stdin) != NULL);
    assert(freopen("subbit.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> (S + 1);

    int i, j, answer = 1, pos = 1;

    if (S[1] == '0') {
        pos++;
    }

    if (S[pos] == 0) {
        cout << answer << '\n';
        return 0;
    }

    int V[35];
    for (i = 1; ; ++i) {
        int ci = i;
        V[0] = 0;
        while (ci) {
            V[++V[0]] = ci & 1;
            ci >>= 1;
        }
        for (j = V[0]; j >= 1; --j) {
            if (V[j] + '0' == S[pos]) {
                ++pos;
                if (S[pos] == 0) {
                    cout << answer + 1 << '\n';
                    return 0;
                }
            }
            ++answer;
        }
    }

	return 0;
}
