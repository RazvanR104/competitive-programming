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

ifstream in("insule.in");
ofstream out("insule.out");

const int NMAX = 110, ISLANDS = 4;
const int dl[] = { 0, 1, 0, -1 };
const int dc[] = { 1, 0, -1, 0 };

int N, M;
int nri[ISLANDS];
char MAP[NMAX][NMAX];
bool witness[NMAX][NMAX];
queue<pair<int, int> > Q;

bool Check(int x, int y, char value) {
    for (int i = 0; i < 4; ++i)
        if (MAP[x + dl[i]][y + dc[i]] == value) return true;
    return false;
}

int main() {
    int i, j, x, y, k, new_x, new_y, len;

    in >> N >> M;
    in.getline(MAP[0], NMAX);
    for (i = 1; i <= N; ++i)
        in.getline(MAP[i] + 1, NMAX);

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (MAP[i][j] == '0' || witness[i][j]) continue;
            ++nri[MAP[i][j] - '0'];
            witness[i][j] = true;

            Q.push(make_pair(i, j));
            while(!Q.empty()) {
                x = Q.front().first;
                y = Q.front().second;
                Q.pop();

                for (k = 0; k < 4; ++k) {
                    new_x = x + dl[k];
                    new_y = y + dc[k];

                    if (new_x < 1 || new_y < 1 || new_x > N || new_y > M) continue;
                    if (MAP[new_x][new_y] != MAP[x][y]) continue;
                    if (witness[new_x][new_y]) continue;
                    witness[new_x][new_y] = true;
                    Q.push(make_pair(new_x, new_y));
                }
            }
        }
    }

    out << nri[1] << ' ' << nri[2] << ' ' << nri[3] << ' ';

    int new_i, new_j;
    queue<pair<pair<int, int>, int> > Q2;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            if (MAP[i][j] == '0' && Check(i, j, '1')) {
                Q2.push(make_pair(make_pair(i, j), 1));
                witness[i][j] = true;
            }

    while(!Q2.empty()) {
        i = Q2.front().first.first;
        j = Q2.front().first.second;
        len = Q2.front().second;
        Q2.pop();

        if (Check(i, j, '2')) {
            out << len << '\n';
            return 0;
        }

        for (k = 0; k < 4; ++k) {
            new_i = i + dl[k];
            new_j = j + dc[k];

            if (MAP[new_i][new_j] != '0') continue;
            if (witness[new_i][new_j]) continue;

            witness[new_i][new_j] = true;
            Q2.push(make_pair(make_pair(new_i, new_j), len + 1));
        }
    }

    in.close(), out.close();
    return 0;
}
