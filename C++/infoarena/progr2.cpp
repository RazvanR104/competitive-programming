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

ifstream in("progr2.in");
ofstream out("progr2.out");

typedef long long int64;
typedef vector<pair<int, int> >::iterator _iterator;

const int NMAX = 2010, MOD = 666013;

int T, N;
int value[NMAX];
vector<pair<int, int> > H[MOD];

inline int exists(const int &value) {
    if (value < 0) return false;
    int pos = value % MOD;

    for (_iterator it = H[pos].begin(); it != H[pos].end(); ++it)
        if (it->first == value) return it->second;

    return -1;
}

inline void hash_insert(const int &value, const int &pos) {
    H[value % MOD].push_back(make_pair(value, pos));
}

int main() {
    int i, j;

    for (in >> T; T; --T) {
        memset(H, 0, sizeof(H));
        memset(value, 0, sizeof(value));

        for (in >> N, i = 0; i < N; ++i) {
            in >> value[i];
            hash_insert(value[i], i);
        }

        int64 res = 0;
        for (i = 0; i < N - 1; ++i) {
            for (j = i + 1; j < N; ++j) {
                int r = value[j] - value[i], _value = value[j], last_pos = j, pos;
                ++res;
                while((pos = exists(_value += r)) > last_pos) {
                    last_pos = pos;
                    ++res;
                }
            }
        }

        out << res << '\n';
    }

    in.close(), out.close();
    return 0;
}
