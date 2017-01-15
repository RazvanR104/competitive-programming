#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <ctime>

using namespace std;

const short NMAX = 30010;

struct Node {
    short key, pr, size;
    Node *left, *right, *father;

    Node() {
    }
    Node(short key, short pr, short size, Node *left, Node *right, Node *father):
        key(key),
        pr(pr),
        size(size),
        left(left),
        right(right),
        father(father) {
    }
} *T, *nil, *nodes[NMAX];

int N;

inline short Random() {
    return (rand() << 16) ^ rand();
    //return rand();
}

void Update(Node *node) {
    if (node == nil)
        return;
    node->size = node->left->size + node->right->size + 1;
}

pair<Node *, Node *> Split(Node *node, short pos) {
    if (node == nil)
        return {nil, nil};

    if (pos <= node->left->size) {
        auto split = Split(node->left, pos);
        node->left = split.second;
        node->left->father = node;
        split.second = node;
        split.first->father = nil;
        Update(node);
        return split;
    } else {
        auto split = Split(node->right, pos - 1 - node->left->size);
        node->right = split.first;
        node->right->father = node;
        split.first = node;
        split.second->father = nil;
        Update(node);
        return split;
    }
}

Node *Union(Node *left, Node *right) {
    if (left == nil)
        return right;
    if (right == nil)
        return left;

    if (left->pr >= right->pr) {
        left->right = Union(left->right, right);
        left->right->father = left;
        Update(left);
        return left;
    } else {
        right->left = Union(left, right->left);
        right->left->father = right;
        Update(right);
        return right;
    }
}

short Position(Node *node) {
    Node *last = node;
    short ret = 1 + node->left->size;
    while (node->father != nil) {
        if (node->father->right == last)
            ret += 1 + node->father->left->size;
        last = node->father;
        node = node->father;
    }
    return ret;
}

short kth(Node *node, short pos) {
    while (1) {
        if (node == nil)
            return -1;
        if (pos == node->left->size + 1)
            return node->key;
        if (pos <= node->left->size)
            node = node->left;
        else {
            pos -= 1 + node->left->size;
            node = node->right;
        }
    }
}

int main() {
    assert(freopen("order.in", "r", stdin));
    assert(freopen("order.out", "w", stdout));

    srand(time(0));

    cin >> N;

    T = nil = new Node(-1, -1, 0, 0, 0, 0);
    nil->left = nil->right = nil->father = nil;

    int i, j;
    for (i = 1; i <= N; ++i)
        nodes[i] = new Node(i, Random(), 1, nil, nil, nil);

    for (i = 1; i <= N; ++i)
        T = Union(T, nodes[i]);

    short pos = 1, go = 1;
    while (T->size) {
        short where = pos + go % T->size;
        if (where > T->size)
            where -= T->size;
        cout << kth(T, where) << ' ';
        auto spl1 = Split(T, where);
        auto spl2 = Split(spl1.first, where - 1);
        T = Union(spl2.first, spl1.second);
        pos = where - 1;
        if (pos == 0)
            pos = T->size;
        ++go;
    }

    cout << '\n';
    return 0;
}
