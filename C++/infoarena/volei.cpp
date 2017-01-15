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

ifstream in("volei.in");
ofstream out("volei.out");

const int NMAX = 10, QMAX = 33000;

int N, D, Bpos, Fpos;
int DP[QMAX], from[QMAX];
bool used[QMAX];
pair<int, int> S[2 * NMAX], CH[QMAX];
vector<pair<pair<int, int>, pair<int, int> > > res;
queue<int> Q;

bool Check(int value) {
    int i, j, k;
    vector<int> B, F;

    for (i = 0; i < N * 2; ++i) {
        if (value & (1 << i)) F.push_back(i);
        else B.push_back(i);
    }

    int a, b, c, sign, line;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            a = S[B[i]].second - S[F[j]].second;
            b = S[F[j]].first - S[B[i]].first;
            c = S[F[j]].second * S[B[i]].first - S[F[j]].first * S[B[i]].second;

            sign = 1337;
            for (k = 0; k < N; ++k) {
                if (k == i) continue;
                line = a * S[B[k]].first + b * S[B[k]].second + c;
                if (sign == 1337 && line < 0) sign = -1;
                else if (sign == 1337) sign = 1;
                else if ((line > 0 && sign == -1) || (line < 0 && sign == 1)) break;
            }

            if (k < N) continue;

            for (k = 0; k < N; ++k) {
                if (k == j) continue;
                line = a * S[F[k]].first + b * S[F[k]].second + c;
                if ((sign == 1 && line > 0) || (sign == -1 && line < 0)) break;
            }

            if (k >= N) return true;
        }
    }

    return false;
}

bool DistanceOK(int i, int j) {
    return (ceil(sqrt((S[i].first - S[j].first) * (S[i].first - S[j].first) + (S[i].second - S[j].second) * (S[i].second - S[j].second))) <= D);
}

int main() {
    int i, j, x, y, state = 0, new_state;
    char s;

    in >> N >> D;
    for (i = 0; i < N * 2; ++i) {
        in >> x >> y >> s;
        S[i] = make_pair(x, y);
        if (s == 'F') state |= (1 << i);
    }

    used[state] = true;
    DP[state] = 0;

    Q.push(state);

    while (!Q.empty()) {
        state = Q.front();
        Q.pop();
        if (Check(state)) {
            out << DP[state] << '\n';
            int go = state;
            while (from[go]) {
                res.push_back(make_pair(make_pair(S[CH[go].first].first, S[CH[go].first].second), make_pair(S[CH[go].second].first, S[CH[go].second].second)));
                go = from[go];
            }

            for (i = DP[state] - 1; i >= 0; --i)
                out << res[i].first.first << ' ' << res[i].first.second << ' ' << res[i].second.first << ' ' << res[i].second.second << '\n';
            return 0;
        }

        for (i = 0; i < N * 2 - 1; ++i) {
            for (j = i + 1; j < N * 2; ++j) {
                if (((state >> i) & 1) != ((state >> j) & 1) && DistanceOK(i, j)) {
                    new_state = state ^ (1 << i);
                    new_state ^= (1 << j);

                    if (used[new_state]) continue;
                    used[new_state] = true;
                    DP[new_state] = DP[state] + 1;
                    from[new_state] = state;
                    CH[new_state] = make_pair(i, j);

                    Q.push(new_state);
                }
            }
        }
    }

    in.close(), out.close();
    return 0;
}
