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

ifstream in("taxa.in");
ofstream out("taxa.out");

const int NMAX = 1010, oo = 0x3f3f3f3f;
const int dl[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int N, M, li, ci, lf, cf, hSize, Spos;
int P[NMAX][NMAX], Heap[NMAX * NMAX], hpos[NMAX * NMAX];

struct State {
    int ln, col, value;
} S[NMAX * NMAX];

void UpHeap(int pos) {
    while (pos > 1 && S[Heap[pos]].value < S[Heap[pos / 2]].value) {
        hpos[Heap[pos]] = pos / 2;
        hpos[Heap[pos / 2]] = pos;
        swap(Heap[pos], Heap[pos / 2]);
        pos /= 2;
    }
}

void DownHeap(int pos) {
    int son;

    do {
        son = 0;
        if (pos * 2 <= hSize) {
            son = pos * 2;

            if (pos * 2 + 1 <= hSize && S[Heap[pos * 2 + 1]].value < S[Heap[pos * 2]].value)
                son = pos * 2 + 1;

            if (S[Heap[son]].value >= S[Heap[pos]].value) son = 0;
        }

        if (son) {
            hpos[Heap[pos]] = son;
            hpos[Heap[son]] = pos;
            swap(Heap[pos], Heap[son]);
            pos = son;
        }
    } while (son);
}

int main() {
    int i, j, extract;

    in >> N >> M >> li >> ci >> lf >> cf;

    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            in >> P[i][j];
            S[++Spos].ln = i;
            S[Spos].col = j;
            S[Spos].value = oo;
        }


    S[(li - 1) * M + ci].value = 0;
    hpos[(li - 1) * M + ci] = 1;
    Heap[++hSize] = (li - 1) * M + ci;

    int new_ln, new_col, new_state;
    while (hSize) {
        extract = Heap[1];

        if (S[extract].ln == lf && S[extract].col == cf) {
            out << S[extract].value << '\n';
            return 0;
        }

        hpos[(S[Heap[1]].ln - 1) * M + S[Heap[1]].col] = 0;
        Heap[1] = Heap[hSize--];
        hpos[(S[Heap[1]].ln - 1) * M + S[Heap[1]].col] = 1;
        DownHeap(1);

        for (i = 0; i < 8; ++i) {
            new_ln = S[extract].ln + dl[i];
            new_col = S[extract].col + dc[i];
            if (new_ln < 1 || new_col < 1 || new_ln > N || new_col > M) continue;
            new_state = (new_ln - 1) * M + new_col;

            if (P[S[extract].ln][S[extract].col] == P[new_ln][new_col] && S[extract].value < S[new_state].value) {
                S[new_state].value = S[extract].value;
                if (hpos[new_state] == 0) {
                    Heap[++hSize] = new_state;
                    hpos[new_state] = hSize;
                }
                UpHeap(hpos[new_state]);
            } else if (P[S[extract].ln][S[extract].col] != P[new_ln][new_col] && S[extract].value + P[S[extract].ln][S[extract].col] * P[new_ln][new_col] < S[new_state].value) {
                S[new_state].value = S[extract].value + P[S[extract].ln][S[extract].col] * P[new_ln][new_col];
                if (hpos[new_state] == 0) {
                    Heap[++hSize] = new_state;
                    hpos[new_state] = hSize;
                }
                UpHeap(hpos[new_state]);
            }
        }
    }

    in.close(), out.close();
    return 0;
}
