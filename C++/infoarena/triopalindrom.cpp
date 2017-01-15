#include <bits/stdc++.h>

using namespace std;

const int LMAX = 5010;

char S[LMAX];
int cnt[LMAX];

int main() {
    ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    assert(freopen("triopalindrom.in", "r", stdin) != NULL);
    assert(freopen("triopalindrom.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, answer = 0;

    cin >> (S + 1);
    int N = strlen(S + 1);

    for (i = 1; i <= N / 3; ++i) {
        memset(cnt, 0, sizeof(cnt));
        for (j = 1; j + 2 * i <= N; ++j) {
            if (S[j] == S[j + i] && S[j + i] == S[j + 2 * i])
                cnt[j] = 1;
        }

        for (j = 1; j + 2 * i <= N; ++j) {
            if (cnt[j])
                cnt[j] += cnt[j - 1];

            if (cnt[j] >= i)
                ++answer;
        }
    }

    cout << answer << '\n';
    return 0;
}
