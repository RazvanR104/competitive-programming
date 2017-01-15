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

typedef unsigned int uint;
typedef vector<uint>::iterator _iterator;

ifstream in("dictree.in");
ofstream out("dictree.out");

const int NMAX = 25010, MOD = 108631, LMAX = 110, MULT1 = 101, MULT2 = 103;

int N, res = 1;
char str[LMAX];
vector<uint> HT[MOD];

bool insert_hash(const uint &hash_key, const uint &_hash_key) {
    int pos = hash_key % MOD;

    for (_iterator it = HT[pos].begin(); it != HT[pos].end(); ++it)
        if (*it == _hash_key) return false;

    HT[pos].push_back(_hash_key);
    return true;
}

int main() {
    in >> N;
    in.getline(str, LMAX);

    while(N--) {
        in.getline(str, LMAX);

        uint hash1 = 0, hash2 = 0;
        for (int i = 0; str[i]; ++i) {
            hash1 = hash1 * MULT1 + str[i] - 'A';
            hash2 = hash2 * MULT2 + str[i] - 'A';

            if (insert_hash(hash1, hash2)) ++res;
        }
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
