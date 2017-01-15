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

ifstream in("zona.in");
ofstream out("zona.out");

const int NMAX = 60;
const int dl[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

int X, Y, N, L;
int Vis[NMAX][NMAX];
bool Map[NMAX][NMAX][4]; //N E S V
bool witness[NMAX][NMAX];

int main() {
    int i, dir, next_X, next_Y;

    in >> X >> Y >> N >> L;
    Vis[X][Y] = -1;
    for (i = 1; i <= L; ++i) {
        in >> dir;
        --dir;

        next_X = X + dl[dir];
        next_Y = Y + dc[dir];

        if (Vis[next_X][next_Y] == 0)
            Vis[next_X][next_Y] = i;

        if (dir == 0)
            Map[X][Y][1] = Map[X][Y + 1][3] = true;
        else if (dir == 1)
            Map[next_X][next_Y][2] = Map[next_X + 1][next_Y][0] = true;
        else if (dir == 2)
            Map[next_X][next_Y][1] = Map[next_X][next_Y + 1][3] = true;
        else
            Map[next_X][next_Y + 1][2] = Map[next_X + 1][next_Y + 1][0] = true;

        X = next_X;
        Y = next_Y;
    }

    out << L - ((Vis[X][Y] == -1) ? (0) : (Vis[X][Y])) << '\n';

    queue<pair<int, int> > Q;
    Q.push(make_pair(1, 1));

    bool included = false;
    if (Map[1][1][0] && Map[1][1][3]) included = true;

    for (i = 1; i <= N; ++i)
        Map[1][i][0] = Map[N][i][2] = Map[i][1][3] = Map[i][N][1] = true;

    int num = 0;
    while(!Q.empty()) {
        int X = Q.front().first;
        int Y = Q.front().second;
        Q.pop();

        for (i = 0; i < 4; ++i) {
            if (Map[X][Y][i]) continue;
            int new_X = X + dl[i];
            int new_Y = Y + dc[i];
            if (witness[new_X][new_Y]) continue;
            witness[new_X][new_Y] = true;
            Q.push(make_pair(new_X, new_Y));
            ++num;
        }
    }

    if (included) out << num << '\n';
    else out << N * N - num << '\n';
    in.close(), out.close();
    return 0;
}
