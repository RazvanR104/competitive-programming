#include <fstream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

ofstream out("sablon2.out");

const int LMAX = 1 << 10;

int N;
char pattern[LMAX], match[LMAX];
bool l1[LMAX], l2[LMAX];

int main() {
    freopen("sablon2.in", "r", stdin);

    int i, j, k;
    bool *st = l1, *nd = l2;

    scanf("%d\n", &N);
    fgets(pattern + 1, LMAX, stdin);

    for (i = 1; i <= N; ++i) {
        memset(l1, 0, sizeof(l1));
        memset(l2, 0, sizeof(l2));

        fgets(match + 1, LMAX, stdin);

        st[0] = true;

        for (j = 1; pattern[j] != '\n'; ++j) {
            for (k = 1; match[k] != '\n'; ++k) {
                if (pattern[j] == '?' || pattern[j] == match[k])
                    nd[k] = st[k - 1];
                else if (pattern[j] == '*') {
                    if (j == 1) nd[k] = nd[0] = true;
                    else nd[k] = max(st[k], nd[k - 1]);
                }
                else nd[k] = false;
            }
            st[0] = false;
            swap(st, nd);
        }

        if (st[strlen(match + 1) - 1] == true) out << i << '\n';
    }

    fclose(stdin);
    out.close();
    return 0;
}
