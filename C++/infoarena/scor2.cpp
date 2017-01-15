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

ifstream in("scor2.in");
ofstream out("scor2.out");

const int ALPHABET_SIZE = 26, LMAX = 110;

struct Trie {
    int points, last_accessed;
    Trie *children[ALPHABET_SIZE];
    vector<pair<Trie *, int> > coresp;

    Trie() {
        points = last_accessed = 0;
        memset(children, 0, sizeof(children));
    }
} *T;

int N, access = 1;
char line[LMAX], print[LMAX];

Trie *insert_trie(Trie *node, char *str) {
    if (*str < 'A' || *str > 'Z') return node;

    if (node->children[*str - 'A'] == NULL)
        node->children[*str - 'A'] = new Trie();

    return insert_trie(node->children[*str - 'A'], str + 1);
}

bool solve(Trie *node) {
    if (node->points) return true;
    if (node->last_accessed == access) return false;
    node->last_accessed = access;

    for(vector<pair<Trie *, int> >::iterator it = node->coresp.begin(); it != node->coresp.end(); ++it)
        if (solve(it->first)) {
            node->points = it->first->points + it->second;
            return true;
        }

    return false;
}

void DF(Trie *node) {
    if (node->last_accessed) {
        ++access;
        solve(node);
        print[print[0] + 1] = 0;
        out << print + 1 << ' ' << node->points << '\n';
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (node->children[i]) {
            print[++print[0]] = i + 'A';
            DF(node->children[i]);
            --print[0];
        }
}

int main() {
    int pos, add, sgn;
    Trie *address, *coresp;

    in >> N;
    in.getline(line, LMAX);

    T = new Trie();
    while(N--) {
        in.getline(line, LMAX);

        address = insert_trie(T, line);
        address->last_accessed = 1;
        coresp = NULL;
        sgn = 1;

        for (pos = 0; line[pos] != '='; ++pos);
        for (++pos; line[pos] == ' '; ++pos);

        if (line[pos] >= 'A' && line[pos] <= 'Z') {
            coresp = insert_trie(T, line + pos);
            coresp->last_accessed = 1;

            for (++pos; line[pos] != '-' && line[pos] != '+'; ++pos);
            if (line[pos] == '-') sgn = -1;

            for (++pos; line[pos] < '0' || line[pos] > '9'; ++pos);
            for (add = 0; line[pos] >= '0' && line[pos] <= '9'; ++pos)
                add = add * 10 + line[pos] - '0';

            address->coresp.push_back(make_pair(coresp, sgn * add));
            coresp->coresp.push_back(make_pair(address, (-sgn * add)));
        }
        else {
            for (add = 0; line[pos] >= '0' && line[pos] <= '9'; ++pos)
                add = add * 10 + line[pos] - '0';
            address->points = add;
        }
    }

    DF(T);

    in.close(), out.close();
    return 0;
}
