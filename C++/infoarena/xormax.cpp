#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, BMAX = 20;

int N;
int V[NMAX];

struct Trie {
    int pos;
    Trie *next[2];

    Trie():
        pos(0) {
        memset(next, 0, sizeof next);
    }
} *T;

void Insert(Trie *node, int value, int bit, int pos) {
    if (bit == -1) {
        node->pos = pos;
        return;
    }

    int bit_value = (value & (1 << bit)) > 0;

    if (node->next[bit_value] == 0)
        node->next[bit_value] = new Trie();

    Insert(node->next[bit_value], value, bit - 1, pos);
}

int Query(Trie *node, int value, int bit) {
    if (bit == -1)
        return node->pos;

    int bit_value = (value & (1 << bit)) > 0;

    if (node->next[!bit_value])
        return Query(node->next[!bit_value], value, bit - 1);
    return Query(node->next[bit_value], value, bit - 1);
}

int main() {
    assert(freopen("xormax.in", "r", stdin));
    assert(freopen("xormax.out", "w", stdout));

    int i;

    T = new Trie();
    Insert(T, 0, BMAX, 0);

    int Max = -1, start = -1, stop = -1;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> V[i];
        V[i] ^= V[i - 1];

        int pos = Query(T, V[i], BMAX);

        if (Max < (V[pos] ^ V[i])) {
            Max = (V[pos] ^ V[i]);
            start = pos + 1;
            stop = i;
        }

        Insert(T, V[i], BMAX, i);
    }

    cout << Max << ' ' << start << ' ' << stop << '\n';
    return 0;
}
