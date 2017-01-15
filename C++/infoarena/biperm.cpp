#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10010;

int N;
int P[2][NMAX], cost[NMAX], ans[2][NMAX];
bool seen[NMAX];
vector<int> C[NMAX], where[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("biperm.in", "r", stdin) != NULL);
    assert(freopen("biperm.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> N;
    for (i = 0; i < 2; ++i)
        for (j = 1; j <= N; ++j) {
            cin >> P[i][j];
            where[P[i][j]].push_back(j);
        }

    int num = 0;
    int answer = 1;
    for (i = 1; i <= N; ++i) {
        if (seen[i])
            continue;

        int col = i, ln = 0;
        do {
            seen[col] = 1;
            C[num].push_back(P[ln][col]);
            ln ^= 1;
            C[num].push_back(P[ln][col]);
            int last = P[ln][col];

            ln ^= 1;

            if (C[num].front() == C[num].back())
                break;

            for (int now : where[last])
                if (now != col) {
                    col = now;
                    break;
                }

            if (P[ln][col] != last) {
                ++cost[num];
                swap(P[0][col], P[1][col]);
            }
        } while (1);

        if (C[num].size() != 2)
            answer *= 2;

        ++num;
    }

    int Min = 0;

    for (i = 0; i < num; ++i)
            Min += min(cost[i], int(C[i].size()) / 2 - cost[i]);

    cout << answer << ' ' << Min << '\n';

    memset(seen, 0, sizeof(seen));
    j = 0;
    for (i = 1; i <= N; ++i) {
        if (seen[i])
            continue;
        int col = i, ln = 0;
        for (int k = 0; k < int(C[j].size()); k += 2) {
            seen[col] = 1;
            int now = C[j][k];
            int nxt = C[j][k + 1];

            ans[ln][col] = now;
            ln ^= 1;
            ans[ln][col] = nxt;
            ln ^= 1;

            for (int now : where[nxt])
                if (now != col) {
                    col = now;
                    break;
                }
        }
        ++j;
    }

    for (i = 0; i < 2; ++i) {
        for (j = 1; j <= N; ++j)
            cout << ans[i][j] << ' ';
        cout << '\n';
    }

	return 0;
}
