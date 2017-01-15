#include <bits/stdc++.h>

using namespace std;

const int NMAX = 40010;

int N, M;

inline int Random() {
    return (rand() << 16) ^ rand();
}

struct Treap {
    int key, priority, size;
    Treap *left, *right, *father;
    bool rev;

    Treap():
        rev(0) {
    }
    Treap(int key, int priority, int size, Treap *left, Treap *right, Treap *father):
        key(key),
        priority(priority),
        size(size),
        left(left),
        right(right),
        father(father),
        rev(0) {
    }
} *nodes[NMAX], *nil;

void Update(Treap *node) {
    if (node == nil)
        return;

    if (node->rev) {
        node->rev = 0;
        swap(node->left, node->right);
        node->left->rev ^= 1;
        node->right->rev ^= 1;
    }
    node->size = node->left->size + node->right->size + 1;
}

Treap *Stack[NMAX];
int GetPos(Treap *node) {
    Treap *curr = node;
    int top = -1;
    while (curr != nil) {
        Stack[++top] = curr;
        curr = curr->father;
    }
    while (top >= 0) {
        Treap *now = Stack[top--];
        Update(now);
    }

    int pos = 0;
    Treap *last = node->right;
    while (node != nil) {
        if (node->right == last)
            pos += 1 + node->left->size;
        last = node;
        node = node->father;
    }

    return pos;
}

Treap *GetRoot(Treap *node) {
    while (node->father != nil)
        node = node->father;
    return node;
}

Treap *Merge(Treap *left, Treap *right) {
    if (left == nil)
        return right;
    if (right == nil)
        return left;

    Update(left);
    Update(right);

    if (left->priority >= right->priority) {
        left->right = Merge(left->right, right);
        left->right->father = left;
        Update(left);
        return left;
    } else {
        right->left = Merge(left, right->left);
        right->left->father = right;
        Update(right);
        return right;
    }
}

int Unite(Treap *left, Treap *right) {
    Treap *leftroot = GetRoot(left);
    Treap *rightroot = GetRoot(right);

    if (leftroot == rightroot)
        return 0;

    int posleft = GetPos(left);
    int posright = GetPos(right);

    if (posleft == leftroot->size && posright == 1)
        Merge(leftroot, rightroot);
    else if (posleft == 1 && posright == rightroot->size)
        Merge(rightroot, leftroot);
    else if (posleft == 1 && posright == 1) {
        leftroot->rev ^= 1;
        Merge(leftroot, rightroot);
    } else if (posleft == leftroot->size && posright == rightroot->size) {
        rightroot->rev ^= 1;
        Merge(leftroot, rightroot);
    } else
        return 0;
    return 1;
}

pair<Treap *, Treap *> split(Treap *node, int pos) {
    if (node == nil)
        return {nil, nil};

    Update(node);

    if (pos <= node->left->size) {
        auto treaps = split(node->left, pos);
        node->left = treaps.second;
        node->left->father = node;
        Update(node);
        treaps.second = node;
        treaps.second->father = treaps.first->father = nil;
        return treaps;
    } else {
        auto treaps = split(node->right, pos - 1 - node->left->size);
        node->right = treaps.first;
        node->right->father = node;
        Update(node);
        treaps.first = node;
        treaps.first->father = treaps.second->father = nil;
        return treaps;
    }
}

int Split(Treap *A, Treap *B) {
    Treap *stroot = GetRoot(A);
    Treap *ndroot = GetRoot(B);

    if (stroot != ndroot)
        return 0;

    int posA = GetPos(A);
    int posB = GetPos(B);

    if (posB == posA + 1) {
        split(stroot, posA);
        return 1;
    } else if (posA == posB + 1) {
        split(stroot, posB);
        return 1;
    }
    return 0;
}

int kth(Treap *node, int pos) {
    if (node == nil)
        return -1;

    Update(node);
    if (pos == node->left->size + 1)
        return node->key;
    if (pos <= node->left->size)
        return kth(node->left, pos);
    return kth(node->right, pos - 1 - node->left->size);
}

vector<int> DistanceD(Treap *node, int D) {
    if (D == 0)
        return vector<int>(1, node->key);

    Treap *root = GetRoot(node);
    int pos = GetPos(node);
    vector<int> ret;
    if (pos - D >= 1)
        ret.push_back(kth(root, pos - D));
    if (pos + D <= root->size)
        ret.push_back(kth(root, pos + D));
    sort(ret.begin(), ret.end());
    return ret;
}

vector<int> ChainEnds(Treap *node) {
    Treap *root = GetRoot(node);
    int pos = GetPos(node);

    if (root->size == 1)
        return vector<int>(1, root->key);

    vector<int> ret;
    ret.push_back(kth(root, 1));
    ret.push_back(kth(root, root->size));
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    assert(freopen("drumuri4.in", "r", stdin));
    assert(freopen("drumuri4.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &M);
    srand(time(0));

    nil = new Treap(-1, -1, 0, 0, 0, 0);
    nil->left = nil->right = nil->father = nil;
    for (i = 1; i <= N; ++i)
        nodes[i] = new Treap(i, Random(), 1, nil, nil, nil);

    while (M--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            cout << Unite(nodes[x], nodes[y]) << '\n';
        } else if (op == 2) {
            cin >> x >> y;
            cout << Split(nodes[x], nodes[y]) << '\n';
        }
        else if (op == 3) {
            scanf("%d %d", &x, &y);
            vector<int> answer = DistanceD(nodes[x], y);
            cout << answer.size() << ' ';
            for (const int &it: answer)
                cout << it << ' ';
            cout << '\n';
        } else {
            scanf("%d", &x);
            vector<int> answer = ChainEnds(nodes[x]);
            cout << answer.size() << ' ';
            for (const int &it: answer)
                cout << it << ' ';
            cout << '\n';
        }
    }

    return 0;
}
