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
#include <cassert>

using namespace std;

ifstream in("strigat.in");
ofstream out("strigat.out");

const int LMAX = 110, ALPHABET_SIZE = 26;

int N, M, nodes, grad, start, finish;

struct Trie {
    int grad, node;
    char c;
    Trie *child[ALPHABET_SIZE], *fail;

    Trie(const char &);
} *T = new Trie(0);

Trie::Trie(const char &_c) : node(++nodes), c(_c) {
    memset(child, 0, sizeof(child));
    fail = 0;
    grad = 0;
}

char word[LMAX];
vector<Trie *> Q;
int pre[LMAX][LMAX * LMAX], best[LMAX][LMAX * LMAX];
char lit[LMAX][LMAX * LMAX];

void trie_insert(Trie *node, char *str) {
    if (*str == 0) {
        node->grad += grad;
        return;
    }

    if (node->child[*str - 'a'] == 0) node->child[*str - 'a'] = new Trie(*str);
    trie_insert(node->child[*str - 'a'], str + 1);
}

inline void compute_fail() {
    Trie *fail;

    T->fail = T;
    Q.push_back(T);

    while(start <= finish) {
        Trie *node = Q[start++];
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->child[i] == 0) continue;

            for (fail = node->fail; fail->child[i] == 0 && fail != T; fail = fail->fail);
            if (fail->child[i] != 0 && fail->child[i] != node->child[i]) fail = fail->child[i];

            node->child[i]->fail = fail;
            node->child[i]->grad += fail->grad;
            Q.push_back(node->child[i]);
            ++finish;
        }
    }

    T->fail = 0;
}

inline void solve() {
    int i, j, k;

    memset(best, -1, sizeof(best));

    best[0][1] = 0;

    for (i = 0; i < N; ++i) {
        for (j = finish; j >= 0; --j) {
            Trie *node = Q[j];
            if (best[i][node->node] == -1) continue;

            if (node->fail != 0) {
                if (best[i][node->fail->node] < best[i][node->node]) {
                    best[i][node->fail->node] = best[i][node->node];
                    pre[i][node->fail->node] = pre[i][node->node];
                    lit[i][node->fail->node] = lit[i][node->node];
                }
            }

            for (k = 0; k < ALPHABET_SIZE; ++k) {
                if (node->child[k] == 0) continue;
                if (best[i + 1][node->child[k]->node] < best[i][node->node] + node->child[k]->grad) {
                    best[i + 1][node->child[k]->node] = best[i][node->node] + node->child[k]->grad;
                    pre[i + 1][node->child[k]->node] = node->node;
                    lit[i + 1][node->child[k]->node] = k + 'a';
                }
            }
        }
    }

    int sol = -1, pos = -1;

    for (i = 1; i <= nodes; ++i)
        if (sol < best[N][i]) {
            sol = best[N][i];
            pos = i;
        }

    out << sol << '\n';

    string print;
    for (i = N; i; --i) {
        print += lit[i][pos];
        pos = pre[i][pos];
    }

    reverse(print.begin(), print.end());
    out << print << '\n';
}

int main() {
    int i;

    in >> N >> M;

    for (i = 1; i <= M; ++i) {
        in.getline(word, LMAX);
        in.getline(word, LMAX);
        in >> grad;
        trie_insert(T, word);
    }

    compute_fail();
    solve();

    in.close(), out.close();
    return 0;
}
