#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, Mask = 0xff;

int N, K, _pos;
int DP[NMAX], F[NMAX], DP2[NMAX], V[NMAX];
int values[NMAX], aux[NMAX];
char str[NMAX];

int Query(int pos) {
    ++pos;
    int ret = 0;
    for ( ; pos; pos -= pos & (-pos))
        ret = max(ret, F[pos]);
    return ret;
}

void Update(int pos, int value) {
    if (pos == -1)
        return;
    ++pos;
    for ( ; pos < N + 10; pos += pos & (-pos))
        F[pos] = max(F[pos], value);
}

void RadixSort() {
    int i;
    int cnt[1 << 8], index[1 << 8];

    memset(cnt, 0, sizeof cnt);
    for (i = 0; i < _pos; ++i)
        ++cnt[values[i] & Mask];

    index[0] = 0;
    for (i = 1; i < (1 << 8); ++i)
        index[i] = cnt[i - 1] + index[i - 1];

    for (i = 0; i < _pos; ++i)
        aux[index[values[i] & Mask]++] = values[i];

    memset(cnt, 0, sizeof cnt);
    for (i = 0; i < _pos; ++i)
        ++cnt[(aux[i] >> 8) & Mask];

    index[0] = 0;
    for (i = 1; i < (1 << 8); ++i)
        index[i] = cnt[i - 1] + index[i - 1];

    for (i = 0; i < _pos; ++i)
        values[index[(aux[i] >> 8) & Mask]++] = aux[i];

    memset(cnt, 0, sizeof cnt);
    for (i = 0; i < _pos; ++i)
        ++cnt[(values[i] >> 16) & Mask];

    index[0] = 0;
    for (i = 1; i < (1 << 8); ++i)
        index[i] = cnt[i - 1] + index[i - 1];

    for (i = 0; i < _pos; ++i)
        aux[index[(values[i] >> 16) & Mask]++] = values[i];

    memset(cnt, 0, sizeof cnt);
    for (i = 0; i < _pos; ++i)
        ++cnt[(aux[i] >> 24) & Mask];

    index[0] = 0;
    for (i = 1; i < (1 << 8); ++i)
        index[i] = cnt[i - 1] + index[i - 1];

    for (i = 0; i < _pos; ++i)
        values[index[(aux[i] >> 24) & Mask]++] = aux[i];
}

int main() {
    assert(freopen("blis.in", "r", stdin) != NULL);
    assert(freopen("blis.out", "w", stdout) != NULL);

    int i, j, k;

    cin >> K >> (str + 1);
    N = strlen(str + 1);

    for (i = 1; i <= N; ++i)
        str[i] -= '0';

    if (K > N)
        K = N;

    int ans1 = 0;
    for (i = K; i <= N; ++i) {
        int now = 0;
        for (j = 0; j < K; ++j)
            now |= (int(str[i - j]) << j);
        ans1 = max(ans1, now);
    }
    cout << ans1 << '\n';

    int ans2 = 1;
    deque<pair<int, int>> willupdate;
    for (i = 1; i <= K; ++i) {
        _pos = 0;
        willupdate.clear();
        for (j = i; j <= N; ++j) {
            V[j] = 0;
            for (k = 0; k < i; ++k)
                V[j] |= (int(str[j - k]) << k);
            if (i > 1 && V[j] < (1 << (i - 1)))
                continue;
            values[_pos++] = V[j];
        }
        sort(values, values + _pos);
        //RadixSort();

        for (j = i; j <= N; ++j) {
            int now = V[j];
            if (i > 1 && now < (1 << (i - 1))) {
                willupdate.push_back({-1, 0});
                if (int(willupdate.size()) >= i) {
                    Update(willupdate.front().first, willupdate.front().second);
                    willupdate.pop_front();
                }
                continue;
            }
            int pos = lower_bound(values, values + _pos, now) - values + 1;

            DP2[j] = DP[j - i] + 1;
            DP2[j] = max(DP2[j], Query(pos - 1) + 1);
            ans2 = max(ans2, DP2[j]);

            willupdate.push_back({pos, DP2[j]});
            if (int(willupdate.size()) >= i) {
                Update(willupdate.front().first, willupdate.front().second);
                willupdate.pop_front();
            }
        }

        for (j = 1; j <= N; ++j) {
            DP[j] = max(DP[j], DP[j - 1]);
            if (j >= i)
                DP[j] = max(DP[j], DP2[j]);
        }
        memset(F, 0, sizeof(int) * (N + 10));
    }
    cout << ans2 << '\n';

    return 0;
}
