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

ifstream in("colaj.in");
ofstream out("colaj.out");

const int NMAX = 110;
const int dl[] = { 0, 1, 0, -1 };
const int dc[] = { 1, 0, -1, 0 };

int N, m, p, x_offset = 0, y_offset = 0;
int X[2 * NMAX], Y[2 * NMAX], FILL[2 * NMAX][2 * NMAX], x1[NMAX], _y1[NMAX], x2[NMAX], y2[NMAX];
queue<pair<int, int> > Q;

int Search(int *source, const int value) {
    int mid, left = 1, right = source[0];
    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
        if (value > source[mid]) left = mid + 1;
        else if (value < source[mid]) right = mid - 1;
        else return mid;
    }

    return 1337; //should never execute
}

int main() {
    int i, j, k, res = 0;

    in >> N >> m >> p;
    for (i = 1; i <= N; ++i) {
        in >> x1[i] >> _y1[i] >> x2[i] >> y2[i];
        X[++X[0]] = x1[i], X[++X[0]] = x2[i];
        Y[++Y[0]] = _y1[i], Y[++Y[0]] = y2[i];
    }

    sort(X + 1, X + X[0] + 1);
    sort(Y + 1, Y + Y[0] + 1);

    if (X[1] > 0) x_offset = 1;
    if (Y[1] > 0) y_offset = 1;

    for (i = 1; i <= N; ++i) {
        int x1p = Search(X, x1[i]), x2p = Search(X, x2[i]), y1p = Search(Y, _y1[i]), y2p = Search(Y, y2[i]);
        for (j = x1p; j < x2p; ++j)
            for (k = y1p; k < y2p; ++k)
                FILL[j + x_offset][k + y_offset] = 1;
    }

    int x_limit = 2 * N + x_offset;
    int y_limit = 2 * N + y_offset;

    if (X[X[0]] < m) ++x_limit;
    if (Y[Y[0]] < p) ++y_limit;

    int new_i, new_j, extracted_i, extracted_j;
    for (i = 1; i < x_limit; ++i) {
        for (j = 1; j < y_limit; ++j) {
            if (FILL[i][j]) continue;
            FILL[i][j] = 1;
            ++res;
            Q.push(make_pair(i, j));
            while(!Q.empty()) {
                extracted_i = Q.front().first;
                extracted_j = Q.front().second;
                Q.pop();
                for (k = 0; k < 4; ++k) {
                    new_i = extracted_i + dl[k];
                    new_j = extracted_j + dc[k];
                    if (new_i < 1 || new_i >= x_limit || new_j < 1 || new_j >= y_limit) continue;
                    if (FILL[new_i][new_j]) continue;
                    FILL[new_i][new_j] = 1;
                    Q.push(make_pair(new_i, new_j));
                }
            }
        }
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
