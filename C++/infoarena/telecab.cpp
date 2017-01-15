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

ifstream in("telecab.in");
ofstream out("telecab.out");

const int KMAX = 1010, SMAX = 1010, NMAX = 100010, HMAX = 12, oo = 0x3f3f3f3f;

int N, K, S;
int H[NMAX], NUM[HMAX];
int DP[KMAX][SMAX];
vector<int> path;

inline int Distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int i, j, resA = 0, where = -1;

    in >> N >> K >> S;
    for (i = 1; i <= N; ++i) {
        in >> H[i];
        ++NUM[H[i]];
    }

    bool seek = false;
    for (i = 1; i <= N; ++i) {
        --NUM[H[i]];
        if (seek && H[i] <= H[path[path.size() - 1]]) continue;
        path.push_back(i);
        if (i >= K && where == -1) where = path.size() - 1;
        seek = false;
        for (j = H[i] + 1; j <= 10; ++j)
            if (NUM[j]) {
                seek = true;
                break;
            }
    }

    for (i = 0; i < (int)path.size() - 1; ++i)
        resA += Distance(path[i], H[path[i]], path[i + 1], H[path[i + 1]]);
    out << resA << '\n';

    memset(DP, oo, sizeof(DP));

    DP[0][0] = 0;
    for (i = 1; i <= where; ++i) {
        for (j = 0; j <= S; ++j) {
            if (DP[i - 1][j] == oo) continue;
            if (H[path[i]] > H[path[i - 1]]) {
                if (j + H[path[i]] - H[path[i - 1]] > S) break;
                DP[i][j + H[path[i]] - H[path[i - 1]]] = min(DP[i][j + H[path[i]] - H[path[i - 1]]], DP[i - 1][j] + Distance(path[i], H[path[i]], path[i - 1], H[path[i - 1]]));
            } else if (H[path[i]] == H[path[i - 1]])
                DP[i][j] = min(DP[i][j], DP[i - 1][j] + Distance(path[i], H[path[i]], path[i - 1], H[path[i - 1]]));
            else {
                DP[i][j] = min(DP[i][j], DP[i - 1][j] + Distance(path[i], H[path[i]], path[i - 1], H[path[i - 1]]));
                DP[i][j + H[path[i - 1]] - H[path[i]]] = min(DP[i][j + H[path[i - 1]] - H[path[i]]], DP[i - 1][j] + 1);
            }
        }
    }

    int resB = oo;
    for (j = 0; j <= S; ++j) resB = min(resB, DP[where][j]);

    out << resB << '\n';
    in.close(), out.close();
    return 0;
}
