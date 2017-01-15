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

ifstream in("sudest.in");
ofstream out("sudest.out");

const int NMAX = 110;
const int dl[] = { 1, 0 };
const int dc[] = { 0, 1 };

int N, K, plen;
int R[NMAX][NMAX], C[2 * NMAX], M[NMAX][NMAX];
pair<int, int> path[2 * NMAX];

struct State {
    int x, y, cpos;
    State(int _x, int _y, int _cpos) : x(_x), y(_y), cpos(_cpos) {}
    State() {}
} extract;
queue<State> Q;

int main() {
    int i, j;

    in >> N;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= N; ++j)
            in >> R[i][j];

    in >> K;
    for (i = 1; i <= K; ++i) in >> C[i];
    C[K + 1] = 1;

    int new_x, new_y;
    Q.push(State(1, 1, 1));
    M[1][1] = R[1][1];
    while(!Q.empty()) {
        extract = Q.front();
        Q.pop();
        for (i = 0; i < 2; ++i) {
            new_x = extract.x + C[extract.cpos] * dl[i];
            new_y = extract.y + C[extract.cpos] * dc[i];

            if (new_x < 1 || new_y < 1 || new_x > N || new_y > N) continue;
            if (M[new_x][new_y] < M[extract.x][extract.y] + R[new_x][new_y]) {
                M[new_x][new_y] = M[extract.x][extract.y] + R[new_x][new_y];
                Q.push(State(new_x, new_y, extract.cpos + 1));
            }
        }
    }

    out << M[N][N] << '\n';
    path[plen++] = make_pair(N, N);
    int x = N, y = N, mmax, nx, ny;
    while(x != 1 || y != 1) {
        mmax = -1;
        for (i = 0; i < 2; ++i) {
            new_x = x - C[K] * dl[i];
            new_y = y - C[K] * dc[i];
            if (new_x < 1 || new_y < 1 || new_x > N || new_y > N) continue;
            if (M[new_x][new_y] > mmax) {
                mmax = M[new_x][new_y];
                nx = new_x, ny = new_y;
            }
        }
        x = nx, y = ny;
        path[plen++] = make_pair(x, y);
        --K;
    }

    for (i = plen - 1; i >= 0; --i)
        out << path[i].first << ' ' << path[i].second << '\n';

    in.close(), out.close();
    return 0;
}
