#include <bits/stdc++.h>

using namespace std;

const int TMAX = 12, MOD = 543217, NMAX = 5e5 + 10;
//int v[TMAX];

int N;
int64_t ans1[NMAX], ans2[NMAX], sum[NMAX], ans3[NMAX];
bool used[NMAX];

int main() {
    assert(freopen("urat.in", "r", stdin));
    assert(freopen("urat.out", "w", stdout));

    int i, j;

    /*for (i = 1; i <= TMAX; ++i) {
        for (j = 0; j < i; ++j)
            v[j] = j + 1;

        vector<int> ans;
        int answer = 0, cnt = 0;
        do {
            int candidate = 0;
            for (j = 0; j < i - 1; ++j)
                candidate += abs(v[j] - v[j + 1]);
            if (candidate == answer)
                ++cnt;
            else if (candidate > answer) {
                answer = candidate;
                ans = vector<int>(v, v + i);
                cnt = 1;
            }
        } while (next_permutation(v, v + i));

        cerr << i << ' ' << answer << ' ' << cnt << '\n';
        for (const int &it: ans)
            cout << it << ' ';
        cout << "\n\n";
    }*/

    cin >> N;
    ans1[2] = 1;
    ans1[3] = 3;
    int add = 2;
    for (i = 4; i <= N; ++i) {
        if (i % 2 == 0)
            add += 2;
        ans1[i] = ans1[i - 1] + add;
    }

    ans2[2] = 2;
    ans2[3] = 4;
    int mult[] = {1, 2};
    int add2[] = {3, 4};
    for (i = 4; i <= N; ++i) {
        ans2[i] = 1ll * ans2[i - 2] * mult[i % 2] % MOD;
        mult[i % 2] += add2[i % 2];
        add2[i % 2] += 2;
        if (mult[i % 2] >= MOD)
            mult[i % 2] -= MOD;
        if (add2[i % 2] >= MOD)
            add2[i % 2] -= MOD;
    }

    cout << ans1[N] << '\n' << ans2[N] << '\n';

    if (N % 2 == 0) {
        sum[N / 2] = N - 1;
        int pos = N / 2 - 2;
        sum[N / 2 - 1] = sum[N / 2] - 1;
        while (pos > 0) {
            sum[pos] = sum[pos + 1] - 2;
            --pos;
        }

        sum[N / 2 + 1] = sum[N / 2] - 1;
        pos = N / 2 + 2;
        while (pos < N) {
            sum[pos] = sum[pos - 1] - 2;
            ++pos;
        }

        ans3[N / 2] = 1;
        ans3[N / 2 + 1] = N;
        used[1] = used[N] = 1;
        for (i = N / 2 - 1; i >= 1; --i) {
            if (ans3[i + 1] - sum[i] > 0 && used[ans3[i + 1] - sum[i]] == 0) {
                ans3[i] = ans3[i + 1] - sum[i];
                used[ans3[i + 1] - sum[i]] = 1;
            }
            else {
                ans3[i] = sum[i] + ans3[i + 1];
                used[ans3[i + 1] + sum[i]] = 1;
            }
        }

        for (i = N / 2 + 1; i < N; ++i) {
            if (ans3[i] - sum[i] > 0 && used[ans3[i] - sum[i]] == 0) {
                ans3[i + 1] = ans3[i] - sum[i];
                used[ans3[i] - sum[i]] = 1;
            }
            else {
                ans3[i + 1] = ans3[i] + sum[i];
                used[ans3[i] + sum[i]] = 1;
            }
        }
    } else {
        sum[(N - 1) / 2 + 1] = N - 1;
        sum[(N - 1) / 2] = N - 2;
        sum[(N - 1) / 2 - 1] = N - 3;
        sum[(N - 1) / 2 + 2] = N - 3;

        int pos = (N - 1) / 2 + 2;
        while (pos < N) {
            sum[pos] = sum[pos - 1] - 2;
            ++pos;
        }

        pos = (N - 1) / 2 - 2;
        while (pos > 0) {
            sum[pos] = sum[pos + 1] - 2;
            --pos;
        }

        ans3[(N + 1) / 2] = 1;
        ans3[(N + 1) / 2 + 1] = N;
        used[1] = used[N] = 1;

        for (i = (N + 1) / 2 - 1; i >= 1; --i) {
            if (ans3[i + 1] - sum[i] > 0 && used[ans3[i + 1] - sum[i]] == 0) {
                ans3[i] = ans3[i + 1] - sum[i];
                used[ans3[i + 1] - sum[i]] = 1;
            }
            else {
                ans3[i] = sum[i] + ans3[i + 1];
                used[sum[i] + ans3[i + 1]] = 1;
            }
        }

        for (i = (N + 1) / 2 + 1; i < N; ++i) {
            if (ans3[i] - sum[i] > 0 && used[ans3[i] - sum[i]] == 0) {
                ans3[i + 1] = ans3[i] - sum[i];
                used[ans3[i] - sum[i]] = 1;
            }
            else {
                ans3[i + 1] = ans3[i] + sum[i];
                used[ans3[i] + sum[i]] = 1;
            }
        }
    }

    for (i = 1; i <= N; ++i)
        cout << ans3[i] << ' ';
    cout << '\n';

    return 0;
}
