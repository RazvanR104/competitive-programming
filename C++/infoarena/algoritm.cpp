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
#include <cassert>

using namespace std;

typedef long long int64;

ifstream in("algoritm.in");
ofstream out("algoritm.out");

const int NMAX = 100010, oo = 0x3fffffff;

int T, N, M, hSize, value;
int Heap[NMAX], pos[NMAX], from[NMAX], D[NMAX];
bool used[NMAX], used_edge[2 * NMAX];
vector<int> G[NMAX];
vector<pair<int, int> > G2[NMAX];
struct Edge {
    int x, y, c;
} E[2 * NMAX];

void UpHeap(int Pos) {
    while (Pos > 1 && D[Heap[Pos]] < D[Heap[Pos / 2]]) {
        pos[Heap[Pos]] = Pos / 2;
        pos[Heap[Pos / 2]] = Pos;
        swap(Heap[Pos], Heap[Pos / 2]);
        Pos /= 2;
    }
}

void DownHeap(int Pos) {
    int Son;
    do {
        Son = 0;
        if (Pos * 2 <= hSize) {
            Son = Pos * 2;
            if (Pos * 2 + 1 <= hSize && D[Heap[Pos * 2 + 1]] < D[Heap[Pos * 2]])
                Son = Pos * 2 + 1;
            if (D[Heap[Pos]] <= D[Heap[Son]]) Son = 0;
        }

        if (Son) {
            pos[Heap[Pos]] = Son;
            pos[Heap[Son]] = Pos;
            swap(Heap[Pos], Heap[Son]);
            Pos = Son;
        }
    }
    while(Son);
}

void DF(int node) {
    used[node] = true;

    for (int i = 0; i < (int)G2[node].size(); ++i) {
        int _node = G2[node][i].first;
        if (used[_node] == false) {
            used_edge[G2[node][i].second] = true;
            out << G2[node][i].second << ' ';
            ++value;
            DF(_node);
        }
    }
}

int main() {
    int i, extract, node;

    for (in >> T; T; --T) {
        memset(used, 0, sizeof(used));
        memset(used_edge, 0, sizeof(used_edge));

        in >> N >> M;
        for (i = 1; i <= N; ++i) G[i].clear();
        for (i = 1; i <= N; ++i) G2[i].clear();

        for (i = 1; i <= M; ++i) {
            in >> E[i].x >> E[i].y >> E[i].c;
            G[E[i].x].push_back(i);
        }

        for (i = 1; i <= N; ++i) D[i] = oo, pos[i] = -1;
        D[1] = 0;

        Heap[++hSize] = 1;
        pos[1] = hSize;

        while(hSize) {
            extract = Heap[1];
            Heap[1] = Heap[hSize--];
            pos[Heap[1]] = 1;
            DownHeap(1);

            if (extract != 1) G2[E[from[extract]].x].push_back(make_pair(extract, from[extract]));

            for (i = 0; i < (int)G[extract].size(); ++i) {
                node = E[G[extract][i]].y;
                if (D[node] > D[extract] + E[G[extract][i]].c) {
                    D[node] = D[extract] + E[G[extract][i]].c;
                    from[node] = G[extract][i];

                    if (pos[node] == -1) {
                        Heap[++hSize] = node;
                        pos[node] = hSize;
                        UpHeap(hSize);
                    } else UpHeap(pos[node]);
                }
            }
        }

        DF(1);
        for (i = 1; i <= M; ++i)
            if (used_edge[i] == false) out << i << ' ';
        out << '\n';

        //cerr << value << '\n';
        //for (i = 1; i <= M; ++i)
          //  if (used[i] == false) out << i << ' ';
        //out << '\n';
    }

    in.close(), out.close();
    return 0;
}
