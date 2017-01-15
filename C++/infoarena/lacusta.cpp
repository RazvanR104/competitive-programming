#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

ifstream in("lacusta.in");
ofstream out("lacusta.out");

const int NMAX = 260;

int N, M;
short DP[NMAX][NMAX];
unsigned char P[NMAX][NMAX];

int main() {
    int i, j, value, min_1, min_2, pos_1, pos_2;

    in >> N >> M;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            in >> value;
            P[i][j] = value;
        }

    DP[1][1] = P[1][1];
    for (i = 1; i <= N; ++i) {
        min_1 = min_2 = pos_1 = pos_2 = 0;

        for (j = 1; j <= M; ++j) {
            if (DP[i][j] == 0) continue;
            if (min_1 == 0 || min_1 > DP[i][j]) {
                min_2 = min_1;
                min_1 = DP[i][j];
                pos_2 = pos_1;
                pos_1 = j;
            }
            else if (min_2 == 0 || min_2 > DP[i][j]) {
                min_2 = DP[i][j];
                pos_2 = j;
            }
        }

        for (j = 1; j <= M; ++j) {
            if (j == pos_1) continue;
            if (DP[i + 1][j] == 0 || DP[i + 1][j] > DP[i][pos_1] + P[i][j] + P[i + 1][j])
                    DP[i + 1][j] = DP[i][pos_1] + P[i][j] + P[i + 1][j];
        }

        if (pos_2 == 0) continue;

        for (j = 1; j <= M; ++j) {
            if (j == pos_2) continue;
            if (DP[i + 1][j] == 0 || DP[i + 1][j] > DP[i][pos_2] + P[i][j] + P[i + 1][j])
                    DP[i + 1][j] = DP[i][pos_2] + P[i][j] + P[i + 1][j];
        }
    }

    int res = DP[N][1] + P[N][M];
    for (i = 2; i < M; ++i) res = min(res, DP[N][i] + P[N][M]);

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
