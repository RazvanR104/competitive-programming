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

ifstream in("dir.in");
ofstream out("dir.out");

const int LMAX = 1610, PMAX = 260, NMAX = 110;

int pos, curpos, ppos, Sort[NMAX];
char str[LMAX], paths[NMAX][PMAX], curpath[PMAX];

void Solve() {
    int savepos;
    if (str[pos] >= 'A' && str[pos] <= 'Z') {
        savepos = curpos;
        while((str[pos] >= 'A' && str[pos] <= 'Z') ||
              (str[pos] >= '0' && str[pos] <= '9'))
            curpath[curpos++] = str[pos++];
        curpath[curpos++] = '\\';
        ++pos;
        Solve();
        while(str[pos] == ',') {
            ++pos;
            Solve();
        }
        curpos = savepos;
        curpath[curpos] = 0;
        ++pos;
    }
    else if (str[pos] >= 'a' && str[pos] <= 'z') {
        savepos = curpos;
        while((str[pos] >= 'a' && str[pos] <= 'z') ||
              (str[pos] >= '0' && str[pos] <= '9'))
            curpath[curpos++] = str[pos++];
        curpath[curpos] = 0;
        memcpy(paths[ppos++], curpath, sizeof(paths[0]));
        curpos = savepos;
        curpath[curpos] = 0;
    }
}

struct Compare {
    bool operator()(const int &lhs, const int &rhs) const {
        int i;
        for (i = 0; paths[lhs][i] && paths[rhs][i]; ++i) {
            if (paths[lhs][i] < paths[rhs][i]) return true;
            if (paths[lhs][i] > paths[rhs][i]) return false;
        }
        if (paths[lhs][i] == 0 && paths[rhs][i]) return true;
        return false;
    }
};

int main() {
    int i;

    in.getline(str, LMAX);
    Solve();

    for (i = 0; i < ppos; ++i)
        Sort[i] = i;
    sort(Sort, Sort + ppos, Compare());

    out << ppos << '\n';
    for (i = 0; i < ppos; ++i)
        out << paths[Sort[i]] << '\n';

    in.close(), out.close();
    return 0;
}
