#include <fstream>
#include <utility>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

ifstream in("parcele.in");
ofstream out("parcele.out");

const int NMAX = 100010;

int DX, DY, N, res, X_max, Y_max;
int tree[2][4 * NMAX], best[NMAX];
vector<int> C[NMAX];
pair<int, int> Point[NMAX];

void update(const int node, const int left, const int right, const int qleft, const int qright, const int value) {
    if (left >= qleft && right <= qright) {
        tree[0][node] += value;
        tree[1][node] += value;
        return;
    }

    int mid = (left + right) / 2;
    if (qleft <= mid) update(node * 2, left, mid, qleft, qright, value);
    if (qright > mid) update(node * 2 + 1, mid + 1, right, qleft, qright, value);

    tree[0][node] = max(tree[0][node * 2], tree[0][node * 2 + 1]) + tree[1][node];
}

void solve() {
    int i, j;
    for (i = 1; i <= N; ++i) C[Point[i].first].push_back(Point[i].second);

    for (i = 0; i <= X_max; ++i) {
        for (j = 0; j < (int)C[i].size(); ++j) update(1, 1, Y_max, C[i][j], C[i][j] + DY, 1);
        if (i - DX - 1 >= 0)
            for (j = 0; j < (int)C[i - DX - 1].size(); ++j) update(1, 1, Y_max, C[i - DX - 1][j], C[i - DX - 1][j] + DY, -1);

        if (i >= 1) best[i] = max(best[i - 1], tree[0][1]);
        else best[i] = tree[0][1];
    }

    memset(tree, 0, sizeof(tree));

    for (i = X_max; i >= 0; --i) {
        for (j = 0; j < (int)C[i].size(); ++j) update(1, 1, Y_max, C[i][j], C[i][j] + DY, 1);
        if (i + DX + 1 <= X_max)
            for (j = 0; j < (int)C[i + DX + 1].size(); ++j) update(1, 1, Y_max, C[i + DX + 1][j], C[i + DX + 1][j] + DY, -1);

        if (i >= 1) res = max(res, best[i - 1] + tree[0][1]);
        else res = max(res, tree[0][1]);
    }

    memset(tree, 0, sizeof(tree));
    memset(C, 0, sizeof(C));
    memset(best, 0, sizeof(best));
}

int main() {
    int i;

    in >> DX >> DY >> N;
    for (i = 1; i <= N; ++i) {
        in >> Point[i].first >> Point[i].second;
        X_max = max(X_max, Point[i].first);
        Y_max = max(Y_max, Point[i].second);
    }

    solve();
    swap(X_max, Y_max);
    swap(DX, DY);
    for (i = 1; i <= N; ++i) swap(Point[i].first, Point[i].second);
    solve();

    out << res << '\n';
    return 0;
}
