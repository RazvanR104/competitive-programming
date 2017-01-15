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

ifstream in("fbsearch.in");
ofstream out("fbsearch.out");

const int NMAX = 100010, LMAX = 1 << 6, ALPHABET_SIZE = 26;

int T, N, M;
char line[LMAX], name[NMAX][LMAX];

inline int get_key(const char &c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return c - 'a';
}

struct Trie {
    Trie *child[ALPHABET_SIZE];
    int best_relevance, pos, relevance;
    char best_char;

    Trie() {
        memset(child, 0, sizeof(child));
        best_relevance = relevance = 0;
        best_char = 0x7f;
        pos = 0;
    }
} *TT;

void Clear(Trie *node) {
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (node->child[i])
            Clear(node->child[i]);
    delete node;
}

void insert_word(Trie *node, char *str, int pos) {
    if (*str == 0) {
        node->pos = pos;
        return;
    }

    if (node->child[get_key(*str)] == 0) node->child[get_key(*str)] = new Trie;
    insert_word(node->child[get_key(*str)], str + 1, pos);

    if (node->best_char > *str) node->best_char = *str;
}

void recursive_update(Trie *node, char *str, int relevance) {
    if (*str == ' ') {
        node->relevance += relevance;
        return;
    }

    recursive_update(node->child[get_key(*str)], str + 1, relevance);

    if (node->best_relevance < node->child[get_key(*str)]->best_relevance) {
        node->best_relevance = node->child[get_key(*str)]->best_relevance;
        node->best_char = *str;
    }
    else if (node->best_relevance == node->child[get_key(*str)]->best_relevance && node->best_char > *str) node->best_char = *str;

    if (node->best_relevance < node->child[get_key(*str)]->relevance) {
        node->best_relevance = node->child[get_key(*str)]->relevance;
        node->best_char = *str;
    }
    else if (node->best_relevance == node->child[get_key(*str)]->relevance && node->best_char > *str) node->best_char = *str;
}

void update_relevance() {
    int i, relevance = 0;
    for (i = 2; line[i] != ' '; ++i);
    for (++i; line[i]; ++i) relevance = relevance * 10 + line[i] - '0';

    recursive_update(TT, line + 2, relevance);
}

Trie *recursive_search(Trie *node, char *str) {
    if (*str == 0) return node;

    if (node->child[get_key(*str)] == 0) return 0;
    return recursive_search(node->child[get_key(*str)], str + 1);
}

int get_pos(Trie *node) {
    if (node->relevance >= node->best_relevance && node->pos) return node->pos;

    return get_pos(node->child[get_key(node->best_char)]);
}

void execute_query() {
    Trie *node = recursive_search(TT, line + 2);

    if (node == 0) {
        out << "Search Bing for " << line + 2 << '\n';
        return;
    }

    out << name[get_pos(node)] << '\n';
}

int main() {
    int i;

    for (in >> T; T; --T) {
        TT = new Trie;

        in >> N >> M;
        in.getline(line, LMAX);

        for (i = 1; i <= N; ++i) {
            in.getline(name[i], LMAX);
            insert_word(TT, name[i], i);
        }

        while(M--) {
            in.getline(line, LMAX);
            switch(line[0]) {
                case 'Q': execute_query(); break;
                case 'U': update_relevance();
            }
        }

        Clear(TT);
        memset(name, 0, sizeof(name));
    }

    in.close(), out.close();
    return 0;
}
