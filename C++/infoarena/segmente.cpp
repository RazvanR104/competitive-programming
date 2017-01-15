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

ifstream in("segmente.in");
ofstream out("segmente.out");

const int NMAX = 1010, oo = 0x3f3f3f3f;

int N, V, H;

struct Segment {
    int x1, y1, x2, y2;
} Vt[NMAX], Ht[NMAX];

inline int Abs(int value) {
    if (value < 0) return (-value);
    return value;
}

int main() {
    int i, j, x1, y1, x2, y2, k;

    in >> N;
    for (i = 1; i <= N; ++i) {
        in >> x1 >> y1 >> x2 >> y2;
        assert(x1 <= x2);
        assert(y1 <= y2);

        if (x1 == x2) {
            Vt[++V].x1 = x1;
            Vt[V].x2 = x2;
            Vt[V].y1 = y1;
            Vt[V].y2 = y2;
        } else {
            Ht[++H].x1 = x1;
            Ht[H].x2 = x2;
            Ht[H].y1 = y1;
            Ht[H].y2 = y2;
        }
    }

    int bottom, top, curr, D = oo, min1, min2;
    for (i = 1; i < H; ++i) {
        for (j = i + 1; j <= H; ++j) {
            min1 = min2 = oo;
            for (k = 1; k <= V; ++k) {
                bottom = min(Ht[i].y1, Ht[j].y1);
                top = max(Ht[i].y1, Ht[j].y1);
                curr = max(Ht[i].x1 - Vt[k].x1, Ht[j].x1 - Vt[k].x1);
                curr = max(curr, max(Vt[k].x1 - Ht[i].x2, Vt[k].x1 - Ht[j].x2));
                if (curr < 0) curr = 0;

                if (Vt[k].y2 < top)
                    curr = max(curr, top - Vt[k].y2);

                if (Vt[k].y1 > bottom)
                    curr = max(curr, Vt[k].y1 - bottom);

                if (curr <= min1) {
                    min2 = min1;
                    min1 = curr;
                } else if (curr < min2)
                    min2 = curr;
            }
            D = min(D, max(min1, min2));
        }
    }

    out << D << '\n';
    in.close(), out.close();
    return 0;
}
