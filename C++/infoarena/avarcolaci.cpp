#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500010;

int T, N;

int main() {
    assert(freopen("avarcolaci.in", "r", stdin));
    assert(freopen("avarcolaci.out", "w", stdout));

    int i, value;
    fpos_t pos;

    for(scanf("%d", &T); T; --T) {
        scanf("%d", &N);

        fgetpos (stdin, &pos);

        int candidate;
        int cnt = 1;
        scanf("%d", &candidate);

        for (i = 2; i <= N * 2; ++i) {
            scanf("%d", &value);
            if (value != candidate)
                --cnt;
            else ++cnt;
            if (cnt == 0) {
                cnt = 1;
                candidate = value;
            }
        }

        fsetpos(stdin, &pos);
        cnt = 0;
        for (i = 1; i <= 2 * N; ++i) {
            scanf("%d", &value);
            if (value == candidate)
                ++cnt;
        }

        if (cnt > N)
            cout << candidate << '\n';
        else cout << "Mozart\n";
    }

    return 0;
}
