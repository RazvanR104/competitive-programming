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

ifstream in("trie.in");
ofstream out("trie.out");

const int LMAX = 1 << 5, CMAX = 26;

char line[LMAX];

struct TRIE {
    int children, cnt;
    TRIE *child[CMAX];

    TRIE() {
        memset(child, 0, sizeof(child));
        children = cnt = 0;
    }
} *T = new TRIE;

void insert_word(TRIE *node, char *word) {
    if (*word == 0) {
        ++node->cnt;
        return;
    }

    if (node->child[*word - 'a'] == 0) {
        node->child[*word - 'a'] = new TRIE;
        ++node->children;
    }

    insert_word(node->child[*word - 'a'], word + 1);
}

void delete_word(TRIE *node, char *word) {
    if (*word == 0) {
        --node->cnt;
        return;
    }

    delete_word(node->child[*word - 'a'], word + 1);

    if (node->child[*word - 'a']->cnt == 0 && node->child[*word - 'a']->children == 0) {
        delete node->child[*word - 'a'];
        node->child[*word - 'a'] = 0;
        --node->children;
        return;
    }
}

int count_occurrence(TRIE *node, char *word) {
    if (*word == 0) return node->cnt;
    if (node->child[*word - 'a'] == 0) return 0;

    return count_occurrence(node->child[*word - 'a'], word + 1);
}

int max_common_prefix(TRIE *node, char *word, int len) {
    if (*word == 0 || node->child[*word - 'a'] == 0) return len;

    return max_common_prefix(node->child[*word - 'a'], word + 1, len + 1);
}

int main() {
    in.getline(line, LMAX);

    while(!in.eof()) {
        switch(line[0]) {
            case '0': insert_word(T, line + 2); break;
            case '1': delete_word(T, line + 2); break;
            case '2': out << count_occurrence(T, line + 2) << '\n'; break;
            case '3': out << max_common_prefix(T, line + 2, 0) << '\n';
        }
        in.getline(line, LMAX);
    }

    in.close(), out.close();
    return 0;
}
