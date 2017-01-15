#include <bits/stdc++.h>

using namespace std;

const int MMAX = 15, inf = 0x3f3f3f3f;
const double eps = 1e-4;

int H, N, M, P;
int sum[1 << MMAX], from[1 << MMAX], num[1 << MMAX];
double DP[1 << MMAX];

int sign(double value) {
    if (value < -eps)
        return -1;
    if (value > eps)
        return 1;
    return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("scara2.in", "r", stdin) != NULL);
    assert(freopen("scara2.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> H >> N >> M >> P;

    int mask = 1 << M;
    for (i = 0; i < mask; ++i) {
        DP[i] = inf;
        for (j = 0; j < M; ++j)
            if (i & (1 << j)) {
                sum[i] += j + 1;
                ++num[i];
            }
    }

    DP[0] = 0;
    for (i = 1; i < mask; ++i) {
        for (j = i & (i - 1); j > 0; j = (j - 1) & i) {
            if (sum[i ^ j] <= M && DP[i] > DP[j] + (num[i ^ j] > 1 ? P : 0) + double(sum[i ^ j]) / num[i ^ j]) {
                DP[i] = DP[j] + (num[i ^ j] > 1 ? P : 0) + double(sum[i ^ j]) / num[i ^ j];
                from[i] = i ^ j;
            }
        }
        if (sum[i] <= M && DP[i] > DP[0] + (num[i] > 1 ? P : 0) + double(sum[i]) / num[i]) {
            DP[i] = (num[i ^ j] > 1 ? P : 0) + double(sum[i]) / num[i];
            from[i] = i;
        }
    }

    double answer = inf;
    for (i = 1; i < mask; ++i)
        if (num[i] == N && sum[i] == H)
            answer = min(answer, DP[i]);

    cout << fixed << setprecision(2) << answer << '\n';

    vector<vector<int>> Min, now;
    vector<int> temp;

    for (i = 1; i < mask; ++i) {
        if (sign(DP[i] - answer) == 0 && sum[i] == H && num[i] == N) {
            int curr_mask = i;
            now.clear();
            while (curr_mask) {
                temp.clear();
                for (j = 0; j < M; ++j) {
                    if (from[curr_mask] & (1 << j)) {
                        temp.push_back(j + 1);
                    }
                }
                now.push_back(temp);
                curr_mask ^= from[curr_mask];
            }
            sort(now.begin(), now.end());
            if (Min.size() == 0 || now < Min)
                Min = now;
        }
    }

    for (const auto &i : Min)
        for (const auto &j : i)
            cout << j << ' ';
    cout << '\n';

	return 0;
}
