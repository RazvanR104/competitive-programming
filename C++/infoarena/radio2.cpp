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
typedef vector<pair<uint, vector<int> > >::iterator _iterator;
typedef vector<int>::iterator __iterator;

ifstream in("radio2.in");
ofstream out("radio2.out");

const int NMAX = 1000010, LMAX = 2510, MULT = 29;

int N, M, L, K, divider, len, llen;
uint H[NMAX], pw[NMAX];
char str[NMAX], match[LMAX];
unordered_map<uint, vector<int> > HT;

inline bool verify(const int &pos, const int &_pos) {
    int i, j;
    for (i = pos, j = _pos; i < pos + divider; ++i, ++j)
        if (str[i] != match[j]) return false;

    if (_pos > pos) return false;

    int mis = 0;
    for (i = pos - 1, j = _pos - 1; j; --i, --j)
        if (str[i] != match[j]) ++mis;

   // if ()

    for (i = pos + divider, j = _pos + divider; match[j]; ++i, ++j) {
        if (!str[i]) return false;
        if (str[i] != match[j]) ++mis;
    }

    return (mis <= K);
}

int main() {
    int i, j;
    int64 passes = 0;

    in >> N >> M >> L >> K;

    in.getline(str + 1, NMAX);
    in.getline(str + 1, NMAX);
    len = strlen(str + 1);
    pw[0] = 1;
    for (i = 1; str[i]; ++i) {
        H[i] = H[i - 1] * MULT + str[i] - 'a';
        pw[i] = pw[i - 1] * MULT;
    }

    while(M--) {
        HT.clear();
        in.getline(match + 1, LMAX);
        llen = strlen(match + 1);
        divider = strlen(match + 1) / (K + 1);

        for (i = 1; i <= K + 1; ++i) {
            uint _hash = 0;
            j = divider * i;

            while(j < divider * (i + 1))
                _hash = _hash * MULT + match[j++] - 'a';

            HT[_hash].push_back(i);
            ++passes;
        }

        bool done = false;
        for (i = 1; str[i] && !done; ++i) {
            j = i;
            uint _hash = H[i + divider - 1] - pw[divider] * H[i - 1];
            if (HT.count(_hash)) continue;
                //for (vector<int>::iterator it = HT[_hash].begin(); it != HT[_hash].end(); ++it);
                    //if(verify(i, *it)) {
                      //  done = true;
                       // break;
                    //}
        }

        if (done) out << "1\n";
        else out << "0\n";
    }

    in.close(), out.close();
    return 0;
}
