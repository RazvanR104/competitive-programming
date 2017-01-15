#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int NMAX = 250010;

int T, N;
int Z[NMAX], P[NMAX];
int prefix[NMAX];
i64 answer[NMAX];

void Prefix() {
    int q = 0;
    for (int i = 2; i <= N; ++i) {
        while (q && Z[q + 1] != Z[i])
            q = prefix[q];
        if (Z[q + 1] == Z[i])
            ++q;
        prefix[i] = q;
    }
}

int main() {
    assert(freopen("zlego.in", "r", stdin));
    assert(freopen("zlego.out", "w", stdout));

    int i, j;

    for (scanf("%d", &T); T; --T) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i)
            scanf("%d", &Z[i]);
        for (i = 1; i <= N; ++i)
            scanf("%d", &P[i]);

        Prefix();
        memset(answer, 0, sizeof answer);
        for (i = N; i >= 1; --i) {
            answer[i] += P[i];
            answer[prefix[i]] += answer[i];
        }

        for (i = 1; i <= N; ++i)
            cout << answer[i] << '\n';
    }

    return 0;
}
