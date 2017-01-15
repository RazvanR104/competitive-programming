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

ifstream in("amedie.in");
ofstream out("amedie.out");

const int NMAX = 810;

int N, M, Q, pos, median, num, posmedian;
int V[NMAX][NMAX], lt[NMAX * NMAX], rt[NMAX * NMAX], where[NMAX][NMAX];

struct Cell {
    int ln, col, value;
    bool operator<(const Cell &rhs) const {
        if (value < rhs.value) return true;
        return false;
    }
} C[NMAX * NMAX];

void Erase(int where) {
    C[where].value = -1;
    rt[lt[where]] = rt[where];
    lt[rt[where]] = lt[where];
    if (where == median)
        median = rt[where];
    else if (where < median)
        --posmedian;
}

void MoveMedian(int pos) {
    while (pos > posmedian) {
        median = rt[median];
        ++posmedian;
    }

    while (pos < posmedian) {
        median = lt[median];
        --posmedian;
    }
}

int main() {
    int i, j;

    in >> N >> M >> Q;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            in >> V[i][j];
            C[++pos].ln = i;
            C[pos].col = j;
            C[pos].value = V[i][j];
        }
    }
    sort(C + 1, C + pos + 1);

    for (i = 1; i <= pos; ++i) {
        lt[i] = i - 1;
        rt[i] = i + 1;
        where[C[i].ln][C[i].col] = i;
    }
    rt[pos] = 0;

    if (pos % 2) median = posmedian = pos / 2 + 1;
    else median = posmedian = pos / 2;

    num = pos;
    char opnow;
    int parameter;
    while (Q--) {
        in >> opnow;
        if (opnow == 'L') {
            in >> parameter;
            for (i = 1; i <= M; ++i)
                if (V[parameter][i] != -1) {
                    Erase(where[parameter][i]);
                    V[parameter][i] = -1;
                    --num;
                }
        } else if (opnow == 'C') {
            in >> parameter;
            for (i = 1; i <= N; ++i)
                if (V[i][parameter] != -1) {
                    Erase(where[i][parameter]);
                    V[i][parameter] = -1;
                    --num;
                }
        } else {
            MoveMedian(num / 2 + num % 2);
            out << C[median].value << '\n';
        }
    }

    in.close(), out.close();
    return 0;
}
