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

ifstream in("dijkstra.in");
ofstream out("dijkstra.out");

const int NMAX = 50010, oo = 0x7fffffff;

int N, M, hsize;
int len[NMAX], H[NMAX], pos[NMAX];
vector<pair<int, int> > G[NMAX];

void upheap(int POS) {
    while(POS > 1 && len[H[POS]] < len[H[POS / 2]]) {
        pos[H[POS]] = POS / 2;
        pos[H[POS / 2]] = POS;
        swap(H[POS], H[POS / 2]);
        POS /= 2;
    }
}

void downheap(int POS) {
    int son;
    do {
        son = 0;
        if (POS * 2 <= hsize) {
            son = POS * 2;
            if (POS * 2 + 1 <= hsize && len[H[POS * 2 + 1]] < len[H[POS * 2]])
                son = POS * 2 + 1;
            if (len[H[POS]] <= len[H[son]]) son = 0;
        }

        if (son) {
            pos[H[POS]] = son;
            pos[H[son]] = POS;
            swap(H[POS], H[son]);
            POS = son;
        }
    }
    while(son);
}

int main() {
    int i, j, x, y, c, extr;

    in >> N >> M;
    while(M--) {
        in >> x >> y >> c;
        G[x].push_back(make_pair(y, c));
    }

    for (i = 2; i <= N; ++i) len[i] = oo, pos[i] = -1;
    pos[1] = 1;
    H[++hsize] = 1;

    while(hsize) {
        extr = H[1];
        swap(H[1], H[hsize--]);
        pos[H[1]] = 1;
        downheap(1);

        for (j = 0; j < (int)G[extr].size(); ++j) {
            if (len[G[extr][j].first] > len[extr] + G[extr][j].second) {
                len[G[extr][j].first] = len[extr] + G[extr][j].second;

                if (pos[G[extr][j].first] == -1) {
                    H[++hsize] = G[extr][j].first;
                    pos[G[extr][j].first] = hsize;
                    upheap(hsize);
                }
                else upheap(pos[G[extr][j].first]);
            }
        }
    }

    for (i = 2; i <= N; ++i)
        out << ((len[i] == oo) ? (0) : (len[i])) << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
