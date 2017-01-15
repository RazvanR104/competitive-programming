#include <bits/stdc++.h>

using namespace std;

const int GMAX = 3010;

int N, G;
int last[GMAX], curr[GMAX];
vector<pair<int, int>> rd;
vector<int> lst[GMAX];
vector<int> sum[GMAX];

void MakeTest() {
    int N = 3e5, G = 3e3;

    srand(time(0));
    cout << N << ' ' << G << '\n';
    for (int i = 1; i <= N; ++i)
        cout << rand() % 3000 + 1 << ' ' << rand() % 3000 + 1 << '\n';
}

int main() {
    assert(freopen("ruksak.in", "r", stdin));
    assert(freopen("ruksak.out", "w", stdout));

    //MakeTest();
    //return 0;

    int i, j, k, w, p;

    scanf("%d %d", &N, &G);
    for (i = 1; i <= N; ++i) {
        scanf("%d %d", &w, &p);
        rd.push_back({w, p});
    }
    sort(rd.begin(), rd.end(), greater<pair<int, int>>());

    for (const auto &it: rd) {
        lst[it.first].push_back(it.second);
        if (sum[it.first].size() == 0)
            sum[it.first].push_back(lst[it.first].back());
        else
            sum[it.first].push_back(sum[it.first].back() + lst[it.first].back());
    }

    memset(last, -1, sizeof last);
    last[0] = 0;

    for (i = 0; i <= G; ++i) {
        memset(curr, -1, sizeof curr);

        for (j = 0; j <= G; ++j) {
            curr[j] = max(curr[j], last[j]);
            if (last[j] == -1)
                continue;
            for (k = 0; k < int(sum[i].size()) && j + (k + 1) * i <= G; ++k)
                curr[j + (k + 1) * i] = max(curr[j + (k + 1) * i], last[j] + sum[i][k]);
        }

        memcpy(last, curr, sizeof last);
    }

    int answer = -1;
    for (i = 0; i <= G; ++i)
        answer = max(answer, last[i]);
    cout << answer << '\n';

    return 0;
}
