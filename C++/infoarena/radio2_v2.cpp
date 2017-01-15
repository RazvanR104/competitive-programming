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
typedef vector<pair<uint, int> >::iterator _iterator;

ifstream in("radio1.in");
ofstream out("radio1.out");

const int NMAX = 1000010, LMAX = 2510, MOD = 666013, MULT = 29;

int N, M, L, K, seq_len;
uint H1[NMAX], H2[LMAX], pw = 1;
char str[NMAX], match[LMAX];
vector<pair<uint, int> > HT[MOD];

inline void insert_hash(const uint &hash_key, const int &pos) {
    HT[hash_key % MOD].push_back(make_pair(hash_key, pos));
}

bool verify(const int &str_pos, const int &match_pos) {
    int left_remaining = match_pos - 1, right_remaining = L - match_pos - seq_len;
    if (str_pos - left_remaining < 1 || str_pos + seq_len + right_remaining - 1 > N) return false;

    int mis = 0, i, j;

    for (i = str_pos, j = match_pos; i < str_pos + seq_len; ++i, ++j) {
        if (str[i] != match[j]) ++mis;
        if (mis > K) return false;
    }

    for (i = str_pos - 1, j = match_pos - 1; j; --i, --j) {
        if (str[i] != match[j]) ++mis;
        if (mis > K) return false;
    }

    for (i = str_pos + seq_len, j = match_pos + seq_len; j <= L; ++i, ++j) {
        if (str[i] != match[j]) ++mis;
        if (mis > K) return false;
    }

    return true;
}

int main() {
    int i;
    uint _hash;

    in >> N >> M >> L >> K;
    in.getline(str + 1, NMAX);
    in.getline(str + 1, NMAX);

    seq_len = L / (K + 1);

    for (i = 1; i <= seq_len; ++i) pw *= MULT;

    for (i = 1; i <= N; ++i) {
        H1[i] = H1[i - 1] * MULT + str[i] - 'a';
        if (i >= seq_len) insert_hash(H1[i] - pw * H1[i - seq_len], i - seq_len + 1);
    }

    while(M--) {
        in.getline(match + 1, LMAX);

        for (i = 1; i <= L; ++i) H2[i] = H2[i - 1] * MULT + match[i] - 'a';

        bool done = false;
        for (i = 1; i + seq_len - 1 <= L && !done; i += seq_len) {
            _hash = H2[i + seq_len - 1] - pw * H2[i - 1];
            for (_iterator it = HT[_hash % MOD].begin(); it != HT[_hash % MOD].end(); ++it)
                    if (it->first == _hash && verify(it->second, i)) {
                        done = true;
                        break;
                    }
        }

        if (done) out << "1\n";
        else out << "0\n";
    }

    in.close(), out.close();
    return 0;
}
