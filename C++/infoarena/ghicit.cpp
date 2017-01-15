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

ifstream in("ghicit.in");
ofstream out("ghicit.out");

const int LMAX = 60000, LG2LMAX = 18;

int len;
int Suffix[LG2LMAX][LMAX];
char Str[LMAX];

struct Event {
    int first, second, position;
    bool operator<(const Event &rhs) const {
        if (first < rhs.first) return true;
        if (first > rhs.first) return false;
        if (second < rhs.second) return true;
        return false;
    }
} E[LMAX];

inline int pw2(int value) {
    return (1 << value);
}

int LCP(int pos_1, int pos_2, int lg2) {
    int ret = 0;

    for ( ; lg2 >= 0 && pos_1 <= len && pos_2 <= len; --lg2)
        if (Suffix[lg2][pos_1] == Suffix[lg2][pos_2]) {
            ret += (1 << lg2);
            pos_1 += (1 << lg2);
            pos_2 += (1 << lg2);
        }

    return ret;
}

int main() {
    int i, j;

    in.getline(Str + 1, LMAX);
    len = strlen(Str + 1);

    for (i = 1; i <= len; ++i) Suffix[0][i] = Str[i];

    for (i = 1; pw2(i - 1) < len; ++i) {
        for (j = 1; j <= len; ++j) {
            E[j].first = Suffix[i - 1][j];
            E[j].second = (j + pw2(i - 1) <= len) ? (Suffix[i - 1][j + pw2(i - 1)]) : (-1);
            E[j].position = j;
        }
        sort(E + 1, E + len + 1);

        for (j = 1; j <= len; ++j) {
            if (j > 1 && E[j].first == E[j - 1].first && E[j].second == E[j - 1].second)
                Suffix[i][E[j].position] = Suffix[i][E[j - 1].position];
            else Suffix[i][E[j].position] = j;
        }
    }

    int lg2 = i - 1, res = len - E[1].position + 1;
    for (i = 2; i <= len; ++i)
        res += len - E[i].position + 1 - LCP(E[i - 1].position, E[i].position, lg2);

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
