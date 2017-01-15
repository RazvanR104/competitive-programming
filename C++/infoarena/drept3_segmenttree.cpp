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

ifstream in("drept3.in");
ofstream out("drept3.out");

const int NMAX = 10010;

int N;
int Lazy[4 * NMAX], Area[4 * NMAX], Max[4 * NMAX], Value[4 * NMAX];

struct Event {
    int x, bottom, top, add;

    bool operator<(const Event &rhs) const {
        if (x < rhs.x) return true;
        return false;
    }
} E[2 * NMAX];

void UnLazy(int node, int left, int right) {
    if (Lazy[node]) {
        if (left != right) {
            Lazy[node * 2] += Lazy[node];
            Lazy[node * 2 + 1] += Lazy[node];
        }
        Max[node] += Lazy[node];
        if (Value[node] != -1) {
            Value[node] += Lazy[node];
            Area[node] = (Value[node] > 0) * (right - left + 1);
        }
        Lazy[node] = 0;
    }
}

void Update(int node, int left, int right, int qleft, int qright, int value) {
    UnLazy(node, left, right);

    if (Value[node] != -1 && left >= qleft && right <= qright) {
        Max[node] += value;
        Value[node] += value;
        Area[node] = (Value[node] > 0) * (right - left + 1);
        if (left != right) {
            Lazy[node * 2] += value;
            Lazy[node * 2 + 1] += value;
        }
        return;
    }

    if (left == right) return;

    int mid = (left + right) / 2;
    if (qleft <= mid) Update(node * 2, left, mid, qleft, qright, value);
    if (qright > mid) Update(node * 2 + 1, mid + 1, right, qleft, qright, value);

    UnLazy(node * 2, left, mid);
    UnLazy(node * 2 + 1, mid + 1, right);
    if (Value[node * 2] != Value[node * 2 + 1]) Value[node] = -1;
    else Value[node] = Value[node * 2];
    Area[node] = Area[node * 2] + Area[node * 2 + 1];
    Max[node] = max(Max[node * 2], Max[node * 2 + 1]);
}

int main() {
    int i, j, x, y, d, pos = 0, resA = 0, resB = 0, limit = 0;

    in >> N;
    for (i = 1; i <= N; ++i) {
        in >> x >> y >> d;
        E[++pos].x = x;
        E[pos].bottom = y;
        E[pos].top = y + d - 1;
        E[pos].add = 1;
        E[++pos].x = x + d;
        E[pos].bottom = y;
        E[pos].top = y + d - 1;
        E[pos].add = -1;

        limit = max(limit, y + d - 1);
    }
    sort(E + 1, E + pos + 1);

    for (i = 1, j = 1; i <= pos; i = j) {
        resA += (E[i].x - E[i - 1].x) * Area[1];
        resB = max(resB, Max[1]);

        Update(1, 0, limit, E[i].bottom, E[i].top, E[i].add);
        while (j + 1 <= pos && E[j + 1].x == E[i].x) {
            ++j;
            Update(1, 0, limit, E[j].bottom, E[j].top, E[j].add);
        }
        ++j;
    }

    out << resA << '\n' << resB << '\n';
    in.close(), out.close();
    return 0;
}
