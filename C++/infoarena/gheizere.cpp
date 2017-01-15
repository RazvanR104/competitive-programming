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

typedef long long int64;

ifstream in("gheizere.in");
ofstream out("gheizere.out");

const int NMAX = 260, PMAX = 1010, oo = 0x3f3f3f3f;
const int dl[] = { -1, 0, 1 };
const int dc[] = { 0, 1, 0 };

int N, M, P, e, v;
int MAT[NMAX][NMAX], Time[NMAX][NMAX];
bool Active[PMAX][PMAX];
vector<int> G[NMAX][NMAX];
queue<pair<int, int> > Q;

int main() {
    int i, j, x, y, r, t, d, k;

    in >> N >> M >> P >> e >> v;
    for (i = 1; i <= P; ++i) {
        in >> x >> y >> r >> t >> d;

        for (j = max(1, x - r); j <= x + r && j <= N; ++j)
            for (k = max(1, y - r); k <= y + r && k <= M; ++k)
                G[j][k].push_back(i);

        for (j = t; j <= 1000; j += t + d)
            for (k = j + 1; k <= j + d && k <= 1000; ++k)
                Active[i][k] = true;
    }

    if (e == v && M == 1) {
        out << "1\n";
        return 0;
    }

    Q.push(make_pair(e, 1));
    Time[e][1] = 1;

    int ln, col, new_ln, new_col;
    while (!Q.empty()) {
        ln = Q.front().first;
        col = Q.front().second;
        Q.pop();

        for (i = 0; i < 3; ++i) {
            new_ln = ln + dl[i];
            new_col = col + dc[i];
            if (new_ln < 1 || new_col < 1 || new_ln > N || new_col > M) continue;

            for (j = 0; j < (int)G[new_ln][new_col].size(); ++j)
                if (Active[G[new_ln][new_col][j]][Time[ln][col] + 1]) break;

            if (j < (int)G[new_ln][new_col].size()) continue;

            if (new_ln == v && new_col == M) {
                out << Time[ln][col] + 1 << '\n';
                return 0;
            }

            if (Time[new_ln][new_col] != Time[ln][col] + 1) {
                Time[new_ln][new_col] = Time[ln][col] + 1;
                Q.push(make_pair(new_ln, new_col));
            }
        }
    }


    in.close(), out.close();
    return 0;
}
