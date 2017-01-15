#include <fstream>
#include <vector>

using namespace std;

const int NMAX = 100010, oo = 0x3f3f3f3f;

ifstream in("disconnect.in");
ofstream out("disconnect.out");

int N, M, current = 1;
int euler[2 * NMAX], first[NMAX], last[NMAX], tree[8 * NMAX], lazy[8 * NMAX], level[NMAX];
bool visited[NMAX];
vector<int> G[NMAX];

typedef vector<int>::iterator iter;

void DF(int node) {
    visited[node] = true;
    euler[++euler[0]] = node;
    first[node] = euler[0];

    for (iter i = G[node].begin(); i != G[node].end(); ++i)
        if (!visited[*i]) {
            level[*i] = level[node] + 1;
            DF(*i);
        }

    euler[++euler[0]] = node;
    last[node] = euler[0];
}

void update(int node, int left, int right, int qleft, int qright, int value) {
    if (lazy[node]) {
        tree[node] = lazy[node];
        if (left != right) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
    }

    if (left >= qleft && right <= qright && tree[node] == value) {
        tree[node] = current;
        if (left != right) {
            lazy[node * 2] = current;
            lazy[node * 2 + 1] = current;
        }
        return;
    }

    if (left == right) return;

    int mid = (left + right) / 2;
    if (qleft <= mid) update(node * 2, left, mid, qleft, qright, value);
    if (qright > mid) update(node * 2 + 1, mid + 1, right, qleft, qright, value);

    if (tree[node * 2] == tree[node * 2 + 1]) tree[node] = tree[node * 2];
    else tree[node] = oo;
}

int query(int node, int left, int right, int pos) {
    if (lazy[node]) {
        tree[node] = lazy[node];
        if (left != right) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
    }

    if (left == right) return tree[node];

    int mid = (left + right) / 2, ret;
    if (pos <= mid) ret = query(node * 2, left, mid, pos);
    else ret = query(node * 2 + 1, mid + 1, right, pos);

    if (tree[node * 2] == tree[node * 2 + 1]) tree[node] = tree[node * 2];
    else tree[node] = oo;

    return ret;
}

int main() {
    int i, x, y, type, V = 0, a, b;

    in >> N >> M;
    for (i = 1; i < N; ++i) {
        in >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DF(1);

    for (i = 0; i < M; ++i) {
        in >> type >> x >> y;
        a = x ^ V;
        b = y ^ V;

        if (type == 1) {
            if (level[a] < level[b]) swap(a, b);
            update(1, 1, euler[0], first[a], last[a], query(1, 1, euler[0], first[a]));
            ++current;
        } else if (query(1, 1, euler[0], first[a]) == query(1, 1, euler[0], first[b])) {
            out << "YES\n";
            V = a;
        } else {
            out << "NO\n";
            V = b;
        }
    }

    return 0;
}
