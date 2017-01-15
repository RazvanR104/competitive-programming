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

ifstream in("cenzura.in");
ofstream out("cenzura.out");

const int ALPHABET_SIZE = 26, LMAX = 1000010, WMAX = 110, oo = 0x7fffffff, MMAX = 10010;

int T, N, M;
int imp[LMAX], DP[MMAX];
char str[LMAX], word[WMAX];
vector<int> Int[2][LMAX];
vector<pair<int, int> > Interval;

struct Trie {
    int len;
    bool word;
    vector<int> pos;

    Trie *child[ALPHABET_SIZE], *fail, *fail2;
    Trie() {}
    Trie(int len) {
        memset(child, 0, sizeof(child));
        fail = fail2 = 0;
        this->len = len;
        word = false;
    }
};

int start, finish;
vector<Trie *> Q;

void InsertWord(Trie *AC, char *str) {
    if (*str == 0) {
        AC->word = true;
        return;
    }

    if (AC->child[*str - 'a'] == NULL)
        AC->child[*str - 'a'] = new Trie(AC->len + 1);

    InsertWord(AC->child[*str - 'a'], str + 1);
}

void BF(Trie *AC) {
    int i;
    Trie *fail, *node;

    AC->fail = AC->fail2 = AC;
    Q.push_back(AC);

    while (start <= finish) {
        node = Q[start++];

        for (i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->child[i] == 0) continue;

            for (fail = node->fail; fail->child[i] == 0 && fail != AC; fail = fail->fail);
            if (fail->child[i] != 0 && fail->child[i] != node->child[i]) fail = fail->child[i];

            node->child[i]->fail = fail;

            if (fail->word) node->child[i]->fail2 = fail;
            else node->child[i]->fail2 = fail->fail2;

            Q.push_back(node->child[i]);
            ++finish;
        }
    }

    AC->fail = AC->fail2 = 0;
}

void ABF() {
    int i;
    Trie *node;
    while (finish >= 1) {
        node = Q[finish--];
        for (i = 0; i < (int)node->pos.size(); ++i) {
            if (node->fail2 != Q[0])
                node->fail2->pos.push_back(node->pos[i]);

            if (node->word)
                Interval.push_back(make_pair(node->pos[i] - node->len + 1, node->pos[i]));
        }
    }
}

void Clear() {
    for (int i = 0; i < (int)Q.size(); ++i)
        delete Q[i];
}

int main() {
    int i, j;
    Trie *AC, *_AC;

    for (in >> T; T; --T) {
        AC = new Trie(0);

        in >> N;
        in.getline(str, LMAX);
        in.getline(str, LMAX);

        for (i = 0; i < N; ++i)
            in >> imp[i];

        in >> M;
        in.getline(word, WMAX);
        for (i = 1; i <= M; ++i) {
            in.getline(word, WMAX);
            InsertWord(AC, word);
        }

        BF(AC);

        _AC = AC;
        for (i = 0; str[i]; ++i) {
            for ( ; _AC != AC && _AC->child[str[i] - 'a'] == 0; _AC=_AC->fail);
            if (_AC->child[str[i] - 'a'] != 0) _AC = _AC->child[str[i] - 'a'];
            if (_AC != AC) _AC->pos.push_back(i);
        }

        ABF();

        for (i = 0; str[i]; ++i) {
            Int[0][i].clear();
            Int[1][i].clear();
        }

        sort(Interval.begin(), Interval.end());
        for (i = 0; i < (int)Interval.size(); ++i) {
            Int[0][Interval[i].first].push_back(i + 1);
            Int[1][Interval[i].second].push_back(i + 1);
            DP[i + 1] = oo;
        }

        DP[0] = 0;
        int left = 0, right = 0;
        for (i = 0; str[i]; ++i) {
            for (j = 0; j < (int)Int[0][i].size(); ++j)
                right = max(right, Int[0][i][j]);

            for (j = left + 1; j <= right; ++j)
                DP[j] = min(DP[j], DP[left] + imp[i]);

            for (j = 0; j < (int)Int[1][i].size(); ++j)
                left = max(left, Int[1][i][j]);
        }

        out << DP[Interval.size()] << '\n';

        Clear();
        Interval.clear();
        Q.clear();
        start = finish = 0;
    }

    in.close(), out.close();
    return 0;
}
