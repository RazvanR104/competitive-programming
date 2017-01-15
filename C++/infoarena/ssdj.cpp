#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010;

int N;
int aux[NMAX][NMAX];
char M[NMAX][NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("ssdj.in", "r", stdin);
    freopen("ssdj.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j, k, l;

    cin >> N;
    for (i = 1; i <= N; ++i)
        cin >> (M[i] + 1);

    int answer = 0;
    for (char c = 'b'; c <= 'z'; ++c) {
        for (i = 1; i <= N; ++i)
            for (j = 1; j <= N; ++j) {
                if (M[i][j] == c)
                    aux[i][j] = 1;
                else if (M[i][j] > c)
                    aux[i][j] = 2;
                else
                    aux[i][j] = 0;
            }

        for (i = 2; i <= N; ++i) {
            for (j = 2; j <= N; ++j) {
                if (aux[i][j] == 1) {
                    int Min = 0;
                    for (k = j - 1; k >= 1 && aux[i][k] == 0; --k) {
                        ++Min;
                    }
                    for (k = i - 1; k >= 1 && aux[k][j] == 0; --k) {
                        int now = 0;
                        for (l = j - 1; l >= 1 && now + 1 <= Min; --l) {
                            if (aux[k][l]) {
                                ++answer;
                                break;
                            }
                            ++now;
                        }
                        Min = min(Min, now);
                    }
                } else if (aux[i][j] == 2) {
                    int Min = 0;
                    for (k = j - 1; k >= 1 && aux[i][k] == 0; --k) {
                        ++Min;
                    }
                    for (k = i - 1; k >= 1 && aux[k][j] == 0; --k) {
                        int now = 0;
                        for (l = j - 1; l >= 1 && now + 1 <= Min; --l) {
                            if (aux[k][l] == 1) {
                                ++answer;
                                break;
                            }
                            if (aux[k][l] == 2)
                                break;
                            ++now;
                        }
                        Min = min(Min, now);
                    }
                }
            }
        }
    }

    cout << answer << '\n';

	return 0;
}
