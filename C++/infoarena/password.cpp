#include <bits/stdc++.h>

using namespace std;

const int LMAX = 100010;

char str[LMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("password.in", "r", stdin) != NULL);
    assert(freopen("password.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> str;
    int N = strlen(str);

    int Min = 0, l = 0, p = 1;

    while (p < N && Min + l + 1 < N) {
        if (str[Min + l] == str[(p + l) % N])
            ++l;
        else if (str[Min + l] < str[(p + l) % N]){
            p += l + 1;
            l = 0;
        } else {
            Min = max(Min + l + 1, p);
            p = Min + 1;
            l = 0;
        }
    }

    cout << Min << '\n';
	return 0;
}
