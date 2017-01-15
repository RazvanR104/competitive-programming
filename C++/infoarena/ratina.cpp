#include <fstream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long int64;

ifstream in("ratina.in");
ofstream out("ratina.out");

const int NMAX = 10010, LMAX = 1 << 11, TMAX = 1 << 4, ALPHABET_SIZE = 26, inf = 0x3f3f3f3f;

int N, M, i, t;
int tt[TMAX], len[NMAX];
char word[LMAX];

struct Trie {
    Trie *child[ALPHABET_SIZE];

    Trie() {
        memset(child, 0, sizeof(child));
    }
} *T = new Trie;

vector<Trie *> TT[NMAX];

void insert_word(Trie *node, char *str, int step) {
    if (step) TT[i][step - 1] = node;
    if (str[step] == '\n') return;

    if (node->child[str[step] - 'a'] == 0) node->child[str[step] - 'a'] = new Trie;
    insert_word(node->child[str[step] - 'a'], str, step + 1);
}

int main() {
    freopen("ratina.in", "r", stdin);
    int j, mid, left, right, res;

    //in >> N >> M;
    //in.getline(word, LMAX);
    scanf("%d %d\n", &N, &M);

    for (i = 1; i <= N; ++i) {
        //in.getline(word, LMAX);
        fgets(word, LMAX, stdin);
        len[i] = strlen(word) - 1;
        TT[i].resize(len[i]);
        insert_word(T, word, 0);
    }

    while(M--) {
        scanf("%d", &t);
        int minn = inf;
        for (j = 0; j < t; ++j) {
            //in >> tt[j];
            scanf("%d", &tt[j]);
            minn = min(minn, len[tt[j]]);
        }

        left = 0, right = minn - 1, res = -1;
        for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
            for (j = 1; j < t; ++j)
                if (TT[tt[0]][mid] != TT[tt[j]][mid]) break;
            if (j == t) {
                left = mid + 1;
                res = mid;
            }
            else right = mid - 1;
        }

        out << res + 1 << '\n';
    }

    in.close(), out.close();
    return 0;
}
