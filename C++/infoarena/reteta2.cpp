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

ifstream in("reteta2.in");
ofstream out("reteta2.out");

const int LMAX = 1010, ALPHABET_SIZE = 26;

int pos;
char str[LMAX], Stack[LMAX];

struct Trie {
    int value;
    Trie *child[ALPHABET_SIZE];

    Trie() {
        value = 0;
        memset(child, 0, sizeof(child));
    }
};

Trie *Insert_Word(Trie *node) {
    if (str[pos] < 'a' || str[pos] > 'z') return node;

    if (node->child[str[pos] - 'a']) return Insert_Word(node->child[str[pos++] - 'a']);
    node->child[str[pos] - 'a'] = new Trie();
    return Insert_Word(node->child[str[pos++] - 'a']);
}

void DF(Trie *node, int level) {
    if (node->value) {
        Stack[level] = 0;
        out << Stack << ' ' << node->value << '\n';
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node->child[i] == NULL) continue;
        Stack[level] = i + 'a';
        DF(node->child[i], level + 1);
    }
}

int main() {
    int res = 0, nr;
    Trie *T = new Trie(), *node;

    in.getline(str, LMAX);

    for (pos = 0; str[pos]; ) {
        if (str[pos] >= 'a' && str[pos] <= 'z') {
            node = Insert_Word(T);

            for ( ; str[pos] == ' '; ++pos);
            nr = 0;
            for ( ; str[pos] >= '0' && str[pos] <= '9'; ++pos) nr = nr * 10 + str[pos] - '0';

            node->value += nr;
        }
        else if (str[pos] == ')') {
            ++pos;
            for ( ; str[pos] == ' '; ++pos);
            nr = 0;
            for ( ; str[pos] >= '0' && str[pos] <= '9'; ++pos) nr = nr * 10 + str[pos] - '0';
            res += nr;
        }
        else ++pos;
    }

    out << res << '\n';
    DF(T, 0);

    in.close(), out.close();
    return 0;
}
