#include <fstream>
#include <cstring>

using namespace std;

typedef long long int64;

ifstream in("sub.in");
ofstream out("sub.out");

const int LMAX = 310, CMAX = 26;

int NA, NB, res;
char str[LMAX];

struct Trie {
    int cnt, last_accessed;
    bool invalid;
    Trie *child[CMAX];

    Trie() {
        memset(child, 0, sizeof(child));
        cnt = last_accessed = 0;
    }
} *T = new Trie;

void insert_string(Trie *node, int pos, int access) {
    if (node->last_accessed == access - 1) {
        node->last_accessed = access;
        ++node->cnt;
    }

    if (str[pos] == 0 || node->last_accessed != access) return;

    if (node->child[str[pos] - 'a'] == 0) node->child[str[pos] - 'a'] = new Trie;
    insert_string(node->child[str[pos] - 'a'], pos + 1, access);
}

void mark_as_invalid(Trie *node, int pos) {
    node->invalid = true;

    if (str[pos] == 0 || node->child[str[pos] - 'a'] == 0 || node->child[str[pos] - 'a']->cnt != NA) return;
    mark_as_invalid(node->child[str[pos] - 'a'], pos + 1);
}

void compute_result(Trie *node) {
    if (node->invalid == false) ++res;

    for (int i = 0; i < CMAX; ++i)
        if (node->child[i] && node->child[i]->cnt == NA) compute_result(node->child[i]);
}

int main() {
    int i, j;

    in >> NA;
    in.getline(str, LMAX);

    for (i = 1; i <= NA; ++i) {
        in.getline(str, LMAX);
        j = 0;
        while(str[j]) insert_string(T, j++, i);
    }

    in >> NB;
    in.getline(str, LMAX);
    for (i = 1; i <= NB; ++i) {
        in.getline(str, LMAX);
        j = 0;
        while(str[j]) mark_as_invalid(T, j++);
    }

    compute_result(T);

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
