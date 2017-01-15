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

#define st first
#define nd second

using namespace std;

typedef long long int64;
typedef unsigned int uint;

ifstream in("secv5.in");
ofstream out("secv5.out");

const int MOD = 666013, NMAX = (1 << 20) + 10;

int N, L, U;
uint value[NMAX];
vector<pair<uint, int> > H[MOD];

vector<pair<uint, int> >::iterator get_pos(const uint &value) {
    int pos = value % MOD;

    for (vector<pair<uint, int> >::iterator it = H[pos].begin(); it != H[pos].end(); ++it)
        if (it->first == value) return it;

    return H[pos].end();
}

int64 get_result(const uint &limit) {
    int64 res = 0;
    uint hashes = 0;

    for (int left = 0, right = 0; right < N; ++right) {
        vector<pair<uint, int> >::iterator _hash = get_pos(value[right]);
        if (_hash == H[value[right] % MOD].end()) {
            H[value[right] % MOD].push_back(make_pair(value[right], 1));
            ++hashes;
        }
        else if (_hash->second == 0) ++hashes, ++_hash->second;
        else if (_hash->second) ++_hash->second;

        while(hashes > limit) {
            _hash = get_pos(value[left++]);
            --_hash->second;
            if (_hash->second == 0) --hashes;
        }

        res += right - left + 1;
    }

    return res;
}

int main() {
    int i;
    int64 res = 0;

    in >> N >> L >> U;

    for (i = 0; i < N; ++i) in >> value[i];

    res = get_result(U);
    memset(H, 0, sizeof(H));
    res -= get_result(L - 1);

    out << res << '\n';

    in.close(), out.close();
    return 0;
}
