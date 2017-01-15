#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010;

int N, M;
int ham[NMAX];
bool edge[NMAX][NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("autostrazi2.in", "r", stdin);
    freopen("autostrazi2.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j, x, y;

    cin >> N >> M;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        edge[x][y] = 1;
        edge[y][x] = 1;
    }

    for (i = 1; i <= N; ++i)
        ham[i] = i;

    for (i = 1; i < N; ++i) {
        if (edge[ham[i]][ham[i + 1]] == 0) {
            for (j = 1; j < N; ++j) {
                if (edge[ham[i]][ham[j]] && edge[ham[i + 1]][ham[j + 1]]) {
                    if (i < j)
                        reverse(ham + i + 1, ham + j + 1);
                    else
                        reverse(ham + j + 1, ham + i + 1);
                    break;
                }
            }
        }
    }

    for (i = 1; i <= N; i += 2)
        cout << ham[i] << ' ' << ham[i + 1] << '\n';

	return 0;
}
