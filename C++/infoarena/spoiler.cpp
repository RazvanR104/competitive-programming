#include <bits/stdc++.h>

using namespace std;

const int WMAX = 1000;
typedef uint64_t ui64;

int N, K;
ui64 P[WMAX];

int main() {
    ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen("spoiler.in", "r", stdin);
    freopen("spoiler.out", "w", stdout);
    freopen("debug.err", "w", stderr);
    #endif

    int w, l, i, s;

    cin >> N >> K;

    w = (N + 1) / 2;
    l = K - w;

    ui64 q = 2;
    for (s = K - 1; s >= 0; s--) {
        for (i = min(s, w - 1); i >= s - i; i--) {
            int j = s - i;
            if (i == j)
                P[j] = q + 2 * P[j];
            else if ((i > l) && (j == l))
                P[j] = 2 * P[j];
            else if ((i == w - 1) && (j < l))
                P[j] = 2 * P[j + 1];
            else
                P[j] = q + P[j] + P[j + 1];
        }
        q <<= 1;
    }

    q >>= 1;
    while (P[0] % 2 == 0) {
        P[0] >>= 1;
        q >>= 1;
    }

    cout << P[0] << '\n' << q << '\n';
    return 0;
}
