#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int NMAX = 500010;

int N;
int prefix[NMAX];
i64 V[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("reguli.in", "r", stdin) != NULL);
    assert(freopen("reguli.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> V[i];
        V[i - 1] = V[i] - V[i - 1];
    }

    --N;
    for (i = 2, j = 0; i <= N; ++i) {
        while (j > 0 && V[i] != V[j + 1])
            j = prefix[j];
        if (V[i] == V[j + 1])
            ++j;
        prefix[i] = j;
    }

    cout << N - prefix[N] << '\n';
    for (i = 1; i <= N - prefix[N]; ++i)
        cout << V[i] << '\n';

	return 0;
}
