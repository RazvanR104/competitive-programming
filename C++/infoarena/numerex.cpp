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

typedef unsigned long long uint64;

ifstream in("numerex.in");
ofstream out("numerex.out");

const int NMAX = 100010;

uint64 N, M, pos;
uint64 tree[4 * NMAX], L1[4 * NMAX], L2[4 * NMAX];

inline uint64 Gauss(const uint64 &value) { return (value * (value + 1) >> 1); }

void update(const uint64 node, const uint64 left, const uint64 right, const uint64 qleft, const uint64 qright, const uint64 value) {
    uint64 mid = (left + right) >> 1;

    if (L1[node] || L2[node]) {
        tree[node] += L1[node] * (right - left + 1) + L2[node] * Gauss(right - left + 1);
        if (left != right) {
            L1[node * 2] += L1[node];
            L1[node * 2 + 1] += L1[node] + L2[node] * (mid - left + 1);

            L2[node * 2] += L2[node];
            L2[node * 2 + 1] += L2[node];
        }
        L1[node] = L2[node] = 0;
    }

    if (right < qleft || left > qright || left > right) return;

    if (left >= qleft && right <= qright) {
        tree[node] += value * (pos * (right - left + 1) + Gauss(right - left));
        if (left != right) {
            L1[node * 2] += value * (pos - 1);
            L1[node * 2 + 1] += value * (pos + mid - left);

            L2[node * 2] += value;
            L2[node * 2 + 1] += value;
        }
        pos += right - left + 1;
        return;
    }

    update(node * 2, left, mid, qleft, qright, value);
    update(node * 2 + 1, mid + 1, right, qleft, qright, value);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

uint64 query(const int node, const int left, const int right, const int qleft, const int qright) {
    uint64 mid = (left + right) >> 1;

    if (L1[node] || L2[node]) {
        tree[node] += L1[node] * (right - left + 1) + L2[node] * Gauss(right - left + 1);
        if (left != right) {
            L1[node * 2] += L1[node];
            L1[node * 2 + 1] += L1[node] + L2[node] * (mid - left + 1);

            L2[node * 2] += L2[node];
            L2[node * 2 + 1] += L2[node];
        }
        L1[node] = L2[node] = 0;
    }

    if (left >= qleft && right <= qright) return tree[node];

    uint64 ret = 0;
    if (qleft <= mid) ret += query(node * 2, left, mid, qleft, qright);
    if (qright > mid) ret += query(node * 2 + 1, mid + 1, right, qleft, qright);

    return ret;
}

int main() {
    int op, x, l, k, y;

    in >> N >> M;

    while(M--) {
        in >> op;
        if (op == 0) {
            in >> x >> l >> k;
            pos = 1;
            update(1, 1, N, x, x + l - 1, k);
        }
        else {
            in >> x >> y;
            out << query(1, 1, N, x, y) << '\n';
        }
    }

    in.close(), out.close();
    return 0;
}
