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
typedef unsigned int uint;

const int NMAX = 1010, MULT1 = 2, MULT2 = 5, oo = 0x3f3f3f3f, MOD = 1009;

ifstream in("poveste.in");
ofstream out("poveste.out");

int T, N, M;
uint H1[NMAX][NMAX], H2[NMAX][NMAX], pw1[NMAX], pw2[NMAX];
char P[NMAX][NMAX];
vector<pair<pair<uint, uint>, int> > H[MOD];

int Pos(uint hash_1, uint hash_2) {
    int key = hash_1 % MOD;
    for (int i = 0; i < (int)H[key].size(); ++i)
        if (H[key][i].first.first == hash_1 && H[key][i].first.second == hash_2)
            return H[key][i].second;
    return -1;
}

void Insert(uint hash_1, uint hash_2, int pos) {
    int key = hash_1 % MOD;
    H[key].push_back(make_pair(make_pair(hash_1, hash_2), pos));
}

int MaxDistance(int top, int bottom) {
    int pos, ret = -oo, i;
    uint hash_1, hash_2;

    for (i = 1; i <= M; ++i) {
        hash_1 = H1[i][bottom] - pw1[bottom - top + 1] * H1[i][top - 1];
        hash_2 = H2[i][bottom] - pw2[bottom - top + 1] * H2[i][top - 1];

        pos = Pos(hash_1, hash_2);
        if (pos == -1)
            Insert(hash_1, hash_2, i);
        else {
            ret = max(ret, i - pos + 1);
        }
    }

    return ret;
}

int main() {
    int i, j, AMax, Acurr;

    for (in >> T; T; --T) {
        in >> N >> M;
        in.getline(P[0], NMAX);

        for (i = 1; i <= N; ++i) in.getline(P[i] + 1, NMAX);

        pw1[0] = pw2[0] = 1;
        for (i = 1; i <= N; ++i) {
            pw1[i] = pw1[i - 1] * MULT1;
            pw2[i] = pw2[i - 1] * MULT2;

            for (j = 1; j <= M; ++j) {
                H1[j][i] = H1[j][i - 1] * MULT1 + P[i][j] - '0';
                H2[j][i] = H2[j][i - 1] * MULT2 + P[i][j] - '0';
            }
        }

        AMax = -oo;

        int left, right, mid, get, lines;
        for (i = 1; i <= N; ++i) {
            left = i, right = N;

            /*for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
                get = MaxDistance(i, mid);
                if (get == -oo) {
                    right = mid - 1;
                    continue;
                }

                lines = mid - i + 1;
                Acurr = lines * get;

                AMax = max(AMax, Acurr);

                int _get = MaxDistance(i, mid + 1);
                if ((lines + 1) * _get >= Acurr) left = mid + 1;
                else right = mid - 1;
            }*/

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();

            for (j = 0; j < MOD; ++j)
                H[j].clear();
        }

        out << AMax << '\n';
    }

    in.close(), out.close();
    return 0;
}
