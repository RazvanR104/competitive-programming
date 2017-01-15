#include <bits/stdc++.h>

using namespace std;

const int LMAX = 5010, NMAX = 110, ALPHABET_SIZE = 26;

int N, M;
short state[LMAX][NMAX][2];
short Next[NMAX][LMAX][ALPHABET_SIZE];
char name[LMAX];

int main() {
    assert(freopen("search.in", "r", stdin));
    assert(freopen("search.out", "w", stdout));

    int i, j, maxlen = -1;

    scanf("%d %d\n", &N, &M);

    for (i = 1; i <= N; ++i) {
        gets(name + 1);

        int len = strlen(name + 1);
        maxlen = max(maxlen, len);

        for (j = len; j >= 1; --j) {
            memcpy(Next[i][j], Next[i][j + 1], sizeof Next[i][j]);
            Next[i][j][name[j] - 'a'] = j;
        }
    }

    for (i = 1; i <= N; ++i)
        state[0][i][1] = 1;

    int pos = 0;
    char value;
    while (M--) {
        scanf("%c\n", &value);

        int answer = 0;
        if (value == '-') {
            --pos;
            if (pos <= maxlen) {
                for (i = 1; i <= N; ++i)
                    answer += state[pos][i][1];
            }
        } else {
            ++pos;
            if (pos <= maxlen) {
                for (i = 1; i <= N; ++i) {
                    if (state[pos - 1][i][1] == 0) {
                        state[pos][i][1] = 0;
                        continue;
                    }
                    state[pos][i][0] = Next[i][state[pos - 1][i][0] + 1][value - 'a'];
                    state[pos][i][1] = (state[pos][i][0] > 0);
                    answer += state[pos][i][1];
                }
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
