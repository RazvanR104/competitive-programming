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

ifstream in("invazia.in");
ofstream out("invazia.out");

const int NMAX = 100010, oo = 0x7fffffff;

int N, M, pos = -1, x;
multiset<int> STree[4 * NMAX];

struct UFO {
    int x, y, z;
} UFOs[5 * NMAX];

void UpdateSegmentTree(int node, int left, int right) {
    if (UFOs[pos].x <= left && UFOs[pos].y >= right) {
        STree[node].insert(UFOs[pos].z);
        return;
    }

    if (left == right) return;

    int mid = (left + right) / 2;
    if (UFOs[pos].x <= mid) UpdateSegmentTree(node * 2, left, mid);
    if (UFOs[pos].y > mid) UpdateSegmentTree(node * 2 + 1, mid + 1, right);
}

void EraseFromSegmentTree(int node, int left, int right) {
    if (UFOs[pos].x <= left && UFOs[pos].y >= right) {
        STree[node].erase(STree[node].find(UFOs[pos].z));
        return;
    }

    if (left == right) return;

    int mid = (left + right) / 2;
    if (UFOs[pos].x <= mid) EraseFromSegmentTree(node * 2, left, mid);
    if (UFOs[pos].y > mid) EraseFromSegmentTree(node * 2 + 1, mid + 1, right);
}

int Query(int node, int left, int right) {
    if (left == right) return ((*STree[node].begin() == 0) ? (oo) : (*STree[node].begin()));

    int mid = (left + right) / 2, ret = oo;
    if (x >= left && x <= mid) ret = Query(node * 2, left, mid);
    else if (x > mid && x <= right) ret = Query(node * 2 + 1, mid + 1, right);

    return min(ret, (*STree[node].begin() == 0) ? (oo) : (*STree[node].begin()));
}

int main() {
    char opnow;

    in >> N >> M;

    while(M--) {
        in >> opnow;
        if (opnow == 'I') {
            ++pos;
            in >> UFOs[pos].x >> UFOs[pos].y >> UFOs[pos].z;
            UpdateSegmentTree(1, 1, N);
        }
        else if (opnow == 'E') {
            EraseFromSegmentTree(1, 1, N);
            --pos;
        }
        else {
            in >> x;
            int res = Query(1, 1, N);
            if (res == oo) out << "GUITZZZ!\n";
            else out << res << '\n';
        }
    }

    in.close(), out.close();
    return 0;
}
