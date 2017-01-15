#include <bits/stdc++.h>

using namespace std;

const int NMAX = 30010;

inline int Random() {
    //return (rand() << 16) ^ rand();
    return rand();
}

struct Node {
    short key, priority, size, left, right;
    Node() {
    }
    Node(short key, short priority, short size, short left, short right):
        key(key),
        priority(priority),
        size(size),
        left(left),
        right(right) {
    }
} nodes[NMAX];

int N;

void Update(short node) {
    if (node == 0)
        return;
    nodes[node].size = 1 + nodes[nodes[node].left].size + nodes[nodes[node].right].size;
}

pair<short, short> Split(short node, short pos) {
    if (node == 0)
        return {0, 0};

    if (pos <= nodes[nodes[node].left].size) {
        auto split = Split(nodes[node].left, pos);
        nodes[node].left = split.second;
        split.second = node;
        Update(node);
        return split;
    } else {
        auto split = Split(nodes[node].right, pos - 1 - nodes[nodes[node].left].size);
        nodes[node].right = split.first;
        split.first = node;
        Update(node);
        return split;
    }
}

short Union(short left, short right) {
    if (left == 0)
        return right;
    if (right == 0)
        return left;

    if (nodes[left].priority >= nodes[right].priority) {
        nodes[left].right = Union(nodes[left].right, right);
        Update(left);
        return left;
    } else {
        nodes[right].left = Union(left, nodes[right].left);
        Update(right);
        return right;
    }
}

void Print(short node) {
    if (node == 0)
        return;
    Print(nodes[node].left);
    printf("%d\n", nodes[node].key);
    Print(nodes[node].right);
}

int main() {
    assert(freopen("schi.in", "r", stdin));
    assert(freopen("schi.out", "w", stdout));

    srand(time(0));

    nodes[0] = Node(-1, -1, 0, 0, 0);

    int i, j, pos, T = 0;
    scanf("%d", &N);

    for (i = 1; i <= N; ++i)
        nodes[i] = Node(i, Random(), 1, 0, 0);

    for (i = 1; i <= N; ++i) {
        scanf("%d", &pos);
        auto split = Split(T, pos - 1);
        T = Union(split.first, i);
        T = Union(T, split.second);
    }
    Print(T);

    return 0;
}
