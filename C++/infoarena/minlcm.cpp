#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int T, N;
int cnt[NMAX];

int main() {
    assert(freopen("minlcm.in", "r", stdin));
    assert(freopen("minlcm.out", "w", stdout));

    int i, j;

    for (scanf("%d", &T); T; --T) {
        scanf("%d", &N);

        int Max = 0;
        memset(cnt, 0, sizeof cnt);

        for (i = 1; i <= N; ++i) {
            int val;
            scanf("%d", &val);
            ++cnt[val];
            Max = max(Max, val);
        }

        int64_t answer = 1e18;
        for (i = 1; i <= Max; ++i) {
            int64_t curr = -1;
            for (j = 1; i * j <= Max; ++j)
                if (cnt[i * j]) {
                    curr = j;
                    break;
                }

            if (curr == -1)
                continue;
            for (++j; i * j <= Max; ++j)
                if (cnt[i * j]) {
                    curr *= i * j;
                    break;
                }

            if (i * j <= Max)
                answer = min(answer, curr);
        }

        cout << answer << '\n';
    }

    return 0;
}
