#include <bits/stdc++.h>

using namespace std;

const int NMAX = 25, MMAX = 10010;

int N, M;
int cnt[NMAX], supra[NMAX][NMAX], who[1 << 20];
bool seen[1 << 20][NMAX];

int main() {
    assert(freopen("pokemon3.in", "r", stdin));
    assert(freopen("pokemon3.out", "w", stdout));

    int i, j;

    cin >> N >> M;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= N; ++j)
            cin >> supra[i][j];

    for (i = 1; i <= M; ++i) {
        int value;
        cin >> value;
        ++cnt[value];
        cin >> value;
        ++cnt[value];
        cin >> value;
        ++cnt[value];
    }

    for (i = 0; i < N; ++i)
        who[1 << i] = i + 1;

    int answer = 1e9;
    for (int mask = 1; mask < (1 << N); ++mask) {
        int prev = mask & (mask - 1);
        int bit = prev ^ mask;
        memcpy(seen[mask], seen[prev], sizeof seen[mask]);

        for (i = 1; i <= N; ++i)
            if (supra[who[bit]][i])
                seen[mask][i] = 1;

        for (i = 1; i <= N; ++i)
            if (cnt[i] && seen[mask][i] == 0)
                break;

        if (i > N)
            answer = min(answer, __builtin_popcount(mask));
    }

    if (answer != 1e9)
        cout << answer << '\n';
    else cout << "-1\n";

    return 0;
}
