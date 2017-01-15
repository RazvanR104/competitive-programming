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
typedef vector<pair<int, int> >::iterator _iterator;

ifstream in("oite.in");
ofstream out("oite.out");

const int NMAX = 1 << 11, MOD = 666013;

int C, L;
int sheep[NMAX];
vector<pair<int, int> > H[MOD];

inline _iterator get_iterator(const int &value) {
    int pos = value % MOD;

    for (_iterator it = H[pos].begin(); it != H[pos].end(); ++it)
        if (it->first == value) return it;

    return H[pos].end();
}

inline void insert_hash(const int &value) {
    int pos = value % MOD;
    _iterator it = get_iterator(value);

    if (it == H[pos].end()) H[pos].push_back(make_pair(value, 1));
    else ++it->second;
}

int main() {
    int i, j;
    int64 res = 0;

    in >> C >> L;
    for (i = 0; i < C; ++i) in >> sheep[i];

    for (i = 0; i < C - 1; ++i) {
        for (j = i + 1; j < C; ++j) {
            if (L - sheep[i] - sheep[j] > 0) {
                int value = L - sheep[i] - sheep[j], pos = value % MOD;
                _iterator it = get_iterator(value);
                if (it != H[pos].end()) res += it->second;
            }
        }

        for (j = 0; j < i; ++j) insert_hash(sheep[i] + sheep[j]);
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
