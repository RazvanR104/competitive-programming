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
#include <list>

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

ifstream in("unicat.in");
ofstream out("unicat.out");

const int LMAX = 500010, MOD = 1247119, MULT1 = 9967, MULT2 = 9973;

int DP[2 * LMAX], len;
uint AHash1[LMAX], AHash2[LMAX], BHash1[LMAX], BHash2[LMAX], pw1[LMAX], pw2[LMAX];
char A[LMAX], B[LMAX], parsed[2 * LMAX];
list<pair<uint, uint> > Hash[MOD];

void InsertHash(uint hash_1, uint hash_2) {
    int key = hash_1 % MOD;
    Hash[key].push_back(make_pair(hash_1, hash_2));
}

bool Check(uint hash_1, uint hash_2, bool Erase = false) {
    list<pair<uint, uint> >::iterator it;
    int key = hash_1 % MOD;

    for (it = Hash[key].begin(); it != Hash[key].end(); ++it) {
        if (it->first == hash_1 && it->second == hash_2) {
            if (Erase) Hash[key].erase(it);
            return true;
        }
    }
    return false;
}

void Manacher(char *Str) {
    int i;
    for (len = 0, i = 1; Str[i]; ++i) {
        parsed[++len] = Str[i];
        DP[len] = 1;
        DP[++len] = 0;
    }

    int center = 0, right = 0, mirror, it_left, it_right;
    for (i = 1; i < len - 1; ++i) {
        mirror = 2 * center - i;

        if (i <= right)
            DP[i] = min(DP[mirror], right - i + 1);

        it_left = i - DP[i] + 1;
        it_right = i + DP[i] - 1;

        while (it_left - 2 > 0 && it_right + 2 < len && parsed[it_left - 2] == parsed[it_right + 2]) {
            DP[i] += 2;
            it_right += 2;
            it_left -= 2;
        }

        if (it_right > right) {
            right = it_right;
            center = i;
        }
    }
}

int main() {
    int i, res = 0;
    uint hash_1, hash_2;

    in.getline(A + 1, LMAX);
    in.getline(B + 1, LMAX);

    pw1[0] = pw2[0] = 1;
    for (i = 1; A[i]; ++i) {
        AHash1[i] = AHash1[i - 1] * MULT1 + A[i];
        AHash2[i] = AHash2[i - 1] * MULT2 + A[i];
        pw1[i] = pw1[i - 1] * MULT1;
        pw2[i] = pw2[i - 1] * MULT2;
    }
    for (i = 1; B[i]; ++i) {
        BHash1[i] = BHash1[i - 1] * MULT1 + B[i];
        BHash2[i] = BHash2[i - 1] * MULT2 + B[i];
        pw1[i] = pw1[i - 1] * MULT1;
        pw2[i] = pw2[i - 1] * MULT2;
    }

    Manacher(A);
    int left, right;
    for (i = 1; i < len; ++i) {
        if (i % 2 == 0) {
            left = i / 2 - DP[i] / 2 + 1;
            right = i / 2 + DP[i] / 2;
        } else {
            left = i / 2 - (DP[i] + 1) / 2 + 2;
            right = i / 2 + (DP[i] + 1) / 2;
        }

        for ( ; left <= right; ++left, --right) {
            hash_1 = AHash1[right] - pw1[right - left + 1] * AHash1[left - 1];
            hash_2 = AHash2[right] - pw2[right - left + 1] * AHash2[left - 1];

            if (!Check(hash_1, hash_2)) InsertHash(hash_1, hash_2);
            else break;
        }
    }

    Manacher(B);
    for (i = 1; i < len; ++i) {
        if (i % 2 == 0) {
            left = i / 2 - DP[i] / 2 + 1;
            right = i / 2 + DP[i] / 2;
        } else {
            left = i / 2 - (DP[i] + 1) / 2 + 2;
            right = i / 2 + (DP[i] + 1) / 2;
        }

        for ( ; left <= right; ++left, --right) {
            hash_1 = BHash1[right] - pw1[right - left + 1] * BHash1[left - 1];
            hash_2 = BHash2[right] - pw2[right - left + 1] * BHash2[left - 1];

            if (Check(hash_1, hash_2, true)) ++res;
            else break;
        }
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
