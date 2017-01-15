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

ifstream in("excursie.in");
ofstream out("excursie.out");

const double eps = 1e-3;
const int NMAX = 60, DMAX = 110;
const int dl[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

int N, M;
int MAT[NMAX][NMAX];
double LMax;
double State[NMAX][NMAX][2];

double Abs(const double &value) {
    if (value < 0) return -value;
    return value;
}

int main() {
    int i, j, li, ci, lf, cf;
    queue<pair<int, int> > Q;

    in >> N >> M >> LMax;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            in >> MAT[i][j];
    in >> li >> ci >> lf >> cf;

    Q.push(make_pair(li, ci));

    int ln, col, new_ln, new_col;
    double effort, distance;
    while (!Q.empty()) {
        ln = Q.front().first;
        col = Q.front().second;
        Q.pop();

        for (i = 0; i < 4; ++i) {
            new_ln = ln + dl[i];
            new_col = col + dc[i];
            if (new_ln < 1 || new_col < 1 || new_ln > N || new_col > M) continue;

            distance = sqrt((MAT[new_ln][new_col] - MAT[ln][col]) * (MAT[new_ln][new_col] - MAT[ln][col]) + 1);
            if (MAT[ln][col] < MAT[new_ln][new_col])
                effort = (MAT[new_ln][new_col] - MAT[ln][col]) * distance;
            else if (MAT[ln][col] == MAT[new_ln][new_col])
                effort = 1;
            else effort = (MAT[ln][col] - MAT[new_ln][new_col]) * distance / 2;
            if (State[new_ln][new_col][0] == 0) {
                State[new_ln][new_col][0] = State[ln][col][0] + effort;
                State[new_ln][new_col][1] = State[ln][col][1] + distance;
                Q.push(make_pair(new_ln, new_col));
            } else if (State[ln][col][0] + effort < State[new_ln][new_col][0]) {
                State[new_ln][new_col][0] = State[ln][col][0] + effort;
                State[new_ln][new_col][1] = State[ln][col][1] + distance;
                Q.push(make_pair(new_ln, new_col));
            } else if (Abs(State[new_ln][new_col][0] - State[ln][col][0] - effort) <= eps && State[ln][col][1] + distance < State[new_ln][new_col][1]) {
                State[new_ln][new_col][1] = State[ln][col][1] + distance;
                Q.push(make_pair(new_ln, new_col));
            }
        }
    }

    if (LMax - State[lf][cf][1] >= eps)
        out << fixed << setprecision(3) << State[lf][cf][0] << ' ' << State[lf][cf][1] << '\n';
    else out << "-1\n";
    in.close(), out.close();
    return 0;
}
