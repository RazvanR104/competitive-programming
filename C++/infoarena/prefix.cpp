#include <bits/stdc++.h>

using namespace std;

const int LMAX = 1e6 + 10;

int T;
int prefix[LMAX];
char str[LMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("prefix.in", "r", stdin) != NULL);
    assert(freopen("prefix.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i;

    for ((cin >> T).ignore(1); T; --T) {
        cin >> (str + 1);

        prefix[1] = 0;
        int k = 0;
        for (i = 2; str[i]; ++i) {
            while (k > 0 && str[i] != str[k + 1])
                k = prefix[k];
            if (str[i] == str[k + 1])
                ++k;
            prefix[i] = k;
        }

        for (--i; i >= 1; --i) {
            if (prefix[i] && i % (i - prefix[i]) == 0) {
                cout << i << '\n';
                break;
            }
        }

        if (i == 0)
            cout << "0\n";
    }

	return 0;
}
