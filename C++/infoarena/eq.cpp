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

const int BUFFER_SIZE = 1 << 20, NMAX = 100010;

class InputReader {
    public:
        InputReader() {}
        InputReader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline InputReader & operator >> (int &n) {
            n = 0;
            while(!isdigit(buffer[cursor])) {
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            return *this;
        }
        inline void close() {
            fclose(file);
        }
    private:
        int cursor;
        char buffer[BUFFER_SIZE];
        FILE* file;
        inline void advance() {
            ++cursor;
            if(cursor == BUFFER_SIZE) {
                cursor = 0;
                fread(buffer, BUFFER_SIZE, 1, file);
            }
        }
};

InputReader in("eq.in");
ofstream out("eq.out");

struct SegmentTree {
    int ymax, zmin, difmin, difmax, MIN, MAX;
};

int N, M;
int values[NMAX];
SegmentTree tree[4 * NMAX];

void build_tree(const int node, const int left, const int right) {
    if (left == right) {
        tree[node].ymax = tree[node].zmin = tree[node].MIN = tree[node].MAX = values[left];
        return;
    }

    int mid = (left + right) >> 1;
    build_tree(node * 2, left, mid);
    build_tree(node * 2 + 1, mid + 1, right);

    tree[node].MAX = max(tree[node * 2].MAX, tree[node * 2 + 1].MAX);
    tree[node].MIN = min(tree[node * 2].MIN, tree[node * 2 + 1].MIN);

    tree[node].ymax = max(tree[node * 2].ymax, max(tree[node * 2 + 1].ymax, max(tree[node * 2].difmax + tree[node * 2 + 1].MAX, max(tree[node * 2].MAX - tree[node * 2 + 1].MIN + tree[node * 2 + 1].MAX, 2 * tree[node * 2].MAX - tree[node * 2 + 1].MIN))));
    tree[node].zmin = min(tree[node * 2].zmin, min(tree[node * 2 + 1].zmin, min(tree[node * 2].difmin + tree[node * 2 + 1].MIN, min(tree[node * 2].MIN - tree[node * 2 + 1].MAX + tree[node * 2 + 1].MIN, 2 * tree[node * 2].MIN - tree[node * 2 + 1].MAX))));

    tree[node].difmax = max(tree[node * 2].difmax, max(tree[node * 2 + 1].difmax, tree[node * 2].MAX - tree[node * 2 + 1].MIN));
    tree[node].difmin = min(tree[node * 2].difmin, min(tree[node * 2 + 1].difmin, tree[node * 2].MIN - tree[node * 2 + 1].MAX));
}

SegmentTree query(const int node, const int left, const int right, const int qleft, const int qright) {
    SegmentTree rleft, rright, ret;

    if (qleft <= left && qright >= right) return tree[node];

    int mid = (left + right) >> 1;
    if (qleft <= mid) rleft = query(node * 2, left, mid, qleft, qright);
    if (qright > mid) rright = query(node * 2 + 1, mid + 1, right, qleft, qright);

    if (qleft <= mid && qright > mid) {
        ret.MAX = max(rleft.MAX, rright.MAX);
        ret.MIN = min(rleft.MIN, rright.MIN);

        ret.ymax = max(rleft.ymax, max(rright.ymax, max(rleft.difmax + rright.MAX, max(rleft.MAX - rright.MIN + rright.MAX, 2 * rleft.MAX - rright.MIN))));
        ret.zmin = min(rleft.zmin, min(rright.zmin, min(rleft.difmin + rright.MIN, min(rleft.MIN - rright.MAX + rright.MIN, 2 * rleft.MIN - rright.MAX))));

        ret.difmax = max(rleft.difmax, max(rright.difmax, rleft.MAX - rright.MIN));
        ret.difmin = min(rleft.difmin, min(rright.difmin, rleft.MIN - rright.MAX));
    }
    else if (qleft <= mid) ret = rleft;
    else ret = rright;

    return ret;
}

int main() {
    int i, x, y;
    SegmentTree res;

    in >> N >> M;
    for (i = 1; i <= N; ++i) in >> values[i];
    build_tree(1, 1, N);

    while(M--) {
        in >> x >> y;
        res = query(1, 1, N, x, y);
        out << res.ymax + res.zmin << '\n';
    }

    in.close(), out.close();
    return 0;
}
