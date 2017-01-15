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

const int NMAX = 1000010, MOD = 666013, MULT = 10007;

ifstream in("harta2.in");
ofstream out("harta2.out");

int N;
pair<int, int> C[NMAX];
vector<pair<int, int> > HT[MOD];

inline int get_key(const int x, const int y, const int d) {
    int dx = x / d % MOD, dy = y / d % MOD;
    return (dx * MULT + dy) % MOD;
}

inline int _abs(const int &value) {
    if (value < 0) return -value;
    return value;
}

bool hash_insert(const int x, const int y, const int d) {
    int pos = get_key(x, y, d);
    for(vector<pair<int, int> >::iterator it = HT[pos].begin(); it != HT[pos].end(); ++it)
            if ((it->first != x || it->second != y) &&
                abs(x - it->first) < d && abs(y - it->second) < d)
            return false;
    HT[pos].push_back(make_pair(x, y));
    return true;
}

const int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
const int dy[] = { -1, -1, -1, 0, 1, 1, 1, 0 };

bool check(const int x, const int y, const int d) {
    int j, xx = x / d, yy = y / d;
    for (j = 0; j < 8; ++j) {
        int xxx = xx + dx[j], yyy = yy + dy[j];
        if (xxx < 0 || yyy < 0) continue;
        int pos = (xxx % MOD * MULT + yyy) % MOD;
        for(vector<pair<int, int> >::iterator it = HT[pos].begin(); it != HT[pos].end(); ++it)
             if ((it->first != x || it->second != y) &&
                abs(x - it->first) < d && abs(y - it->second) < d)
                return true;
        }
    return false;
}

int main() {
    int i, j, left = 1, right = NMAX - 10, mid, res;

    in >> N;
    for (i = 1; i <= N; ++i) {
        in >> C[i].first >> C[i].second;
        C[i].second *= 3;
    }

    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
        for(i = 0; i < MOD; ++i) HT[i].clear();
        for (i = 1; i <= N; ++i) {
            if (hash_insert(C[i].first, C[i].second, mid) == false) {
                right = mid - 1;
                break;
            }
        }
        if (i <= N) continue;

        for (i = 1; i <= N; ++i) {
            if(check(C[i].first, C[i].second, mid)) {
                right = mid - 1;
                break;
            }
        }

        if (i <= N) continue;

        res = mid;
        left = mid + 1;
    }

    out << fixed << setprecision(3) << (double)res / 3 << '\n';
    in.close(), out.close();
    return 0;
}
