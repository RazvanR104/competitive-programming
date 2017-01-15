#include <bits/stdc++.h>

using namespace std;

const int LMAX = 50010;

int S;
char str[LMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("csir.in", "r", stdin) != NULL);
    assert(freopen("csir.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    for (cin >> S; S; --S) {
        cin >> str;
        int len = strlen(str);

        int Min = 0, Max = 0, pmin = 1, pmax = 1, lmin = 0, lmax = 0;
        while (pmin < len && Min + lmin + 1 < len) {
            if (str[Min + lmin] == str[(pmin + lmin) % len])
                ++lmin;
            else if (str[Min + lmin] < str[(pmin + lmin) % len]) {
                pmin += lmin + 1;
                lmin = 0;
            } else {
                Min = max(pmin, Min + lmin + 1);
                pmin = Min + 1;
                lmin = 0;
            }
        }

        while (pmax < len && Max + lmax + 1 < len) {
            if (str[Max + lmax] == str[(pmax + lmax) % len])
                ++lmax;
            else if (str[Max + lmax] > str[(pmax + lmax) % len]) {
                pmax += lmax + 1;
                lmax = 0;
            } else {
                Max = max(pmax, Max + lmax + 1);
                pmax = Max + 1;
                lmax = 0;
            }
        }

        int A_max = 0, A_min = 0;
        for (int i = 0; i < len; Min = (Min + 1) % len, Max = (Max + 1) % len, ++i) {
            if (str[Max] == 'A') ++A_max;
            if (str[Min] == 'A') ++A_min;
            if (abs(A_max - A_min) > 1) {
                cout << "0\n";
                goto Continue;
            }
        }

        cout << "1\n";
        Continue:;
    }

	return 0;
}
