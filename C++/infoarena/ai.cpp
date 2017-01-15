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

ifstream in("ai.in");
ofstream out("ai.out");

const int NMAX = 1010, oo = 0x7fffffff;
const int dl[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

int N, T1, T2, S1, S2, S3, S4, R1, R2, R3, R4, K;
int M[NMAX][NMAX];
bool visited[NMAX][NMAX];

bool Line(int XA, int YA, int XB, int YB, int XC, int YC) {
    if (XA > XC) {
        swap(XA, XC);
        swap(YA, YC);
    } else if (XA == XC && YA > YC)
        swap(YA, YC);

    if (XB >= XA && XB <= XC)
        if ((YA < YC && YB >= YA && YB <= YC) ||
            (YB <= YA && YB >= YC))
            return (XA * YB + XB * YC + XC * YA - XC * YB - YC * XA - YA * XB == 0);
    return false;
}

struct State {
    int X, Y, time;
    State(int _X, int _Y, int _time) : X(_X), Y(_Y), time(_time) {}
};

int main() {
    int i, j, X, Y, len_max = -oo, time;

    in >> N >> T1 >> T2 >> S1 >> S2 >> S3 >> S4 >> R1 >> R2 >> R3 >> R4;
    M[T1][T2] = 2;
    M[S1][S2] = 3;
    M[S3][S4] = 4;
    in >> K;
    while (K--) {
        in >> X >> Y;
        M[X][Y] = 1;
    }

    int curr_ln, curr_col;
    for (i = 1; i <= N; ++i) {
        curr_ln = 0, curr_col = 0;
        for (j = 1; j <= N; ++j) {
            if (M[i][j] != 1) curr_ln = 0;
            else ++curr_ln;

            if (M[j][i] != 1) curr_col = 0;
            else ++curr_col;

            len_max = max(len_max, max(curr_ln, curr_col));
        }
    }
    out << len_max << '\n';

    queue<State> Q;
    Q.push(State(R1, R2, 0));

    int time1 = -1, time2 = -1, Protected = 0;

    while(!Q.empty()) {
        X = Q.front().X;
        Y = Q.front().Y;
        time = Q.front().time;
        Q.pop();

        if (Line(T1, T2, X, Y, S1, S2) && time1 == -1) {
            ++Protected;
            time1 = time;
        }

        if (Line(T1, T2, X, Y, S3, S4) && time2 == -1) {
            ++Protected;
            time2 = time;
        }

        if (Protected == 2) break;

        for (i = 0; i < 4; ++i) {
            int new_ln = X + dl[i];
            int new_col = Y + dc[i];
            if (new_ln < 1 || new_ln > N || new_col < 1 || new_col > N) continue;
            if (M[new_ln][new_col] == 1 || M[new_ln][new_col] == 2) continue;
            if (visited[new_ln][new_col]) continue;
            visited[new_ln][new_col] = true;

            Q.push(State(new_ln, new_col, time + 1));
        }
    }

    memset(visited, 0, sizeof(visited));
    int time3 = -1, time4 = -1;
    Protected = 0;

    Q = queue<State>();
    Q.push(State(R3, R4, 0));

    while(!Q.empty()) {
        X = Q.front().X;
        Y = Q.front().Y;
        time = Q.front().time;
        Q.pop();

        if (Line(T1, T2, X, Y, S1, S2) && time3 == -1) {
            ++Protected;
            time3 = time;
        }

        if (Line(T1, T2, X, Y, S3, S4) && time4 == -1) {
            ++Protected;
            time4 = time;
        }

        if (Protected == 2) break;

        for (i = 0; i < 4; ++i) {
            int new_ln = X + dl[i];
            int new_col = Y + dc[i];
            if (new_ln < 1 || new_ln > N || new_col < 1 || new_col > N) continue;
            if (M[new_ln][new_col] == 1 || M[new_ln][new_col] == 2) continue;
            if (visited[new_ln][new_col]) continue;
            visited[new_ln][new_col] = true;

            Q.push(State(new_ln, new_col, time + 1));
        }
    }

    int ResA = max(time1, time4);
    int ResB = max(time2, time3);
    if (ResA == -1) ResA = oo;
    if (ResB == -1) ResB = oo;
    out << min(ResA, ResB) << '\n';
    in.close(), out.close();
    return 0;
}
