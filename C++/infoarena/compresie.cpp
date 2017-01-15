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

ifstream in("compresie.in");
ofstream out("compresie.out");

const int LMAX = 1000010, MDIM = 1010;

int pos;
char str[LMAX], mat[MDIM][MDIM];

void Solve(int x1, int y1, int x2, int y2) {
    if (str[pos] == '*') {
        ++pos;
        if (x1 < x2 && y1 < y2) {
            Solve(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
            Solve(x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2, y2);
            Solve((x1 + x2) / 2 + 1, y1, x2, (y1 + y2) / 2);
            Solve((x1 + x2) / 2 + 1, (y1 + y2) / 2 + 1, x2, y2);
        } else if (x1 == x2 && y1 < y2) {
            Solve(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
            Solve(x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2, y2);
        } else {
            Solve(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
            Solve((x1 + x2) / 2 + 1, y1, x2, y2);
        }
    }
    else if (str[pos] >= '0' && str[pos] <= '9') {
        int nr = 0;
        for ( ; str[pos] >= '0' && str[pos] <= '9'; ++pos) nr = nr * 10 + str[pos] - '0';
        int i, j;
        for (i = x1; i <= x2; ++i)
            for (j = y1; j <= y2; ++j)
                mat[i][j] = str[pos];
        ++pos;
        return;
    }
    else if (str[pos] >= 'a' && str[pos] <= 'z') {
        mat[x1][y1] = str[pos++];
    }
}

int main() {
    int res = 0, i, j, len = 0;

    in.getline(str, LMAX);
    for (i = 0; str[i]; ++i) {
        if (str[i] == '*') ++res;
        else if (str[i] >= '0' && str[i] <= '9') {
            int nr = 0;
            for ( ; str[i] >= '0' && str[i] <= '9'; ++i) nr = nr * 10 + str[i] - '0';
            len += nr;
        }
        else if (str[i] >= 'a' && str[i] <= 'z') ++len;
    }

    out << res << '\n';

    len = sqrt(len);
    Solve(1, 1, len, len);

    for (i = 1; i <= len; ++i, out << '\n')
        for (j = 1; j <= len; ++j)
            out << mat[i][j];

    in.close(), out.close();
    return 0;
}
