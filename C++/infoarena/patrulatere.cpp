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

#include <cassert>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long int64;
typedef pair<int64, int64> point;

const int64 NMAX = 260;

ifstream in("patrulatere.in");
ofstream out("patrulatere.out");

int64 N, rx, ry;
int64 BIT[NMAX], res[NMAX][NMAX];
vector<point> P(1, point());
vector<int64> normalization(1, 0), l, r, X(1, 0);

inline int64 LSB(const int64 value) {
    return (value & (-value));
}

bool left_compare(const int64 &lhs, const int64 &rhs) {
    return (1LL * (P[lhs].second - ry) * (P[rhs].first - rx) > 1LL * (P[rhs].second - ry) * (P[lhs].first - rx));
}

bool right_compare(const int64 &lhs, const int64 &rhs) {
    return (1LL * (P[lhs].second - ry) * (P[rhs].first - rx) < 1LL * (P[rhs].second - ry) * (P[lhs].first - rx));
}

inline void split(const int64 pos) {
    for(int64 i = 1; i < (int64)P.size(); ++i) {
        if(i == pos) continue;
        if(P[i].first < P[pos].first) l.push_back(i);
        else r.push_back(i);
    }
}

inline void update(const int64 pos) {
    for(int64 i = pos; i < NMAX; i += LSB(i)) ++BIT[i];
}

inline int64 query(const int64 pos) {
    int64 ret = 0;
    for(int64 i = pos; i; i -= LSB(i)) ret += BIT[i];
    return ret;
}

inline void compute(const int64 pos, const vector<int64> &v) {
    memset(BIT, 0, sizeof(BIT));

    for(int64 i = 1; i < (int64)v.size(); ++i) {
        update(normalization[v[i - 1]]);
        res[pos][v[i]] = query(max(normalization[v[i]], normalization[pos])) - query(min(normalization[v[i]], normalization[pos]));
    }
}

inline void normalize() {
    sort(X.begin() + 1, X.end());
    unique(X.begin() + 1, X.end());

    int64 i;
    for(i = 1; i < (int64)P.size(); ++i) normalization.push_back(lower_bound(X.begin() + 1, X.end(), P[i].first) - X.begin());

    for(i = 1; i < (int64)P.size(); ++i) {
        l.clear(), r.clear();
        split(i);

        rx = P[i].first, ry = P[i].second;
        sort(l.begin(), l.end(), left_compare);
        sort(r.begin(), r.end(), right_compare);

        compute(i, l);
        compute(i, r);
    }
}

int main() {
    int64 i, j, k, x, y, z;

    in >> N;
    int64 C = 1LL * N * (N - 1) * (N - 2) * (N - 3) / 24;

    for(i = 1; i <= N; ++i) {
        in >> x >> y;
        P.push_back(make_pair(x, y));
        X.push_back(x);
    }

    normalize();

    for (i = 1; i < (int64)P.size() - 2; ++i) {
        for (j = i + 1; j < (int64)P.size() - 1; ++j) {
            for (k = j + 1; k < (int64)P.size(); ++k) {
                x = i, y = j, z = k;
                if (P[x].first > P[y].first) swap(x, y);
                if (P[x].first > P[z].first) swap(x, z);
                if (P[y].first > P[z].first) swap(y, z);

                rx = P[x].first, ry = P[x].second;
                int64 points;
                if (right_compare(y, z)) points = res[x][z] - res[x][y] - res[y][z] - 1;
                else points = res[x][y] + res[y][z] - res[x][z];

                assert(points >= 0);

                C -= points;
            }
        }
    }

    out << C << '\n';
    in.close(), out.close();
    return 0;
}
