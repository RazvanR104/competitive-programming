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

ifstream in("dictree.in");
ofstream out("dictree.out");

const int ALPHABET_SIZE = 52, LMAX = 110;

int N, res = 1;
char str[LMAX];

struct Trie {
    Trie *child[ALPHABET_SIZE];

    Trie() {
        memset(child, 0, sizeof(child));
    }
} *T = new Trie;

inline int get_key(const char &c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

void insert_word(Trie *node, char *str) {
    if (*str == 0) return;
    if (node->child[get_key(*str)] == 0) node->child[get_key(*str)] = new Trie, ++res;
    insert_word(node->child[get_key(*str)], str + 1);
}

int main() {
    in >> N;
    in.getline(str, LMAX);

    while(N--) {
        in.getline(str, LMAX);
        insert_word(T, str);
    }

    out << res << '\n';

    in.close(), out.close();
    return 0;
}
