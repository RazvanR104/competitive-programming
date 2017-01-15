#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50010, inf = 0x3f3f3f3f;

int N, S, M;
int disjoint[NMAX], height[NMAX], node[NMAX], value[NMAX], T[4 * NMAX], where[NMAX];

int Root(int node) {
    int father = node;
    while (father != disjoint[father])
        father = disjoint[father];

    int next;
    while (node != father) {
        next = disjoint[node];
        disjoint[node] = father;
        node = next;
    }

    return father;
}

void Unite(int root1, int root2) {
    if (height[root1] > height[root2]) {
        node[root1] = max(node[root1], node[root2]);
        where[node[root1]] = root1;
        value[root1] = max(value[root1], value[root2]);
        disjoint[root2] = root1;
    }
    else {
        node[root2] = max(node[root1], node[root2]);
        where[node[root2]] = root2;
        value[root2] = max(value[root1], value[root2]);
        disjoint[root1] = root2;
        if (height[root1] == height[root2])
            ++height[root2];
    }
}

void Update(int node, int left, int right, int pos, int value) {
    if (left == right && left == pos) {
        T[node] = value;
        return;
    }

    if (left >= right)
        return;

    int mid = (left + right) / 2;
    if (pos <= mid)
        Update(node * 2, left, mid, pos, value);
    else
        Update(node * 2 + 1, mid + 1, right, pos, value);

    T[node] = max(T[node * 2], T[node * 2 + 1]);
}

int Query(int node, int left, int right, int qleft, int qright) {
    if (left >= qleft && right <= qright)
        return T[node];

    if (left >= right)
        return -inf;

    int mid = (left + right) / 2, ret = -inf;
    if (qleft <= mid)
        ret = max(ret, Query(node * 2, left, mid, qleft, qright));
    if (qright > mid)
        ret = max(ret, Query(node * 2 + 1, mid + 1, right, qleft, qright));

    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("tabara2.in", "r", stdin) != NULL);
    assert(freopen("tabara2.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    assert(scanf("%d %d %d", &N, &S, &M) == 3);
    for (i = 1; i <= S; ++i) {
        assert(scanf("%d", &value[i]) == 1);
        disjoint[i] = i;
    }

    char op;
    int a;
    while (M--) {
        assert(scanf("\n%c", &op) == 1);
        if (op == 'U') {
            assert(scanf("%d %d %d", &a, &i, &j) == 3);
            if (a == 1) {
                Unite(Root(i), Root(j));
                int root = Root(i);
                if (node[root])
                    Update(1, 1, N, node[root], value[root]);
            } else {
                int root;
                if (where[i]) {
                    Unite(where[i], Root(j));
                    root = Root(j);
                } else {
                    root = Root(j);
                    node[root] = i;
                    where[i] = root;
                }
                Update(1, 1, N, node[root], value[root]);
            }
        } else {
            assert(scanf("%d %d", &i, &j) == 2);
            cout << Query(1, 1, N, i, j) << '\n';
        }
    }

	return 0;
}
