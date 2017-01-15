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

ifstream in("text3.in");
ofstream out("text3.out");

const int CMAX = 20010, LMAX = 21, ALPHABET_SIZE = 26;

int DP[CMAX], from[CMAX], pos, MAX[ALPHABET_SIZE];
char words[CMAX][LMAX];

int main() {
    int i, j, mmax = -1, maxpos = -1;

    while(in >> words[pos] + 1) {
        words[pos][0] = strlen(words[pos] + 1);
        ++pos;
    }
    out << pos << '\n';

    for (i = 0; i < ALPHABET_SIZE; ++i) MAX[i] = pos;

    DP[pos - 1] = 1;
    MAX[words[pos - 1][1] - 'a'] = pos - 1;
    for (i = pos - 2; i >= 0; --i) {
            from[i] = MAX[words[i][words[i][0]] - 'a'];
            DP[i] = 1 + DP[MAX[words[i][words[i][0]] - 'a']];
            if (DP[i] > mmax) {
                mmax = DP[i];
                maxpos = i;
            }
            if (DP[i] > DP[MAX[words[i][1] - 'a']])
                MAX[words[i][1] - 'a'] = i;
    }

    out << pos -  mmax << '\n';
    for (i = 1; i <= mmax; ++i) {
        out << words[maxpos] + 1 << '\n';
        maxpos = from[maxpos];
    }

    in.close(), out.close();
    return 0;
}
