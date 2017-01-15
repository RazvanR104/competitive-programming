#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50010;

int N;
int A[NMAX];
vector<int> ones, zeroes;

int lg2(int value) {
    int res = -1;
    while (value) {
        ++res;
        value /= 2;
    }
    return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("specsort.in", "r", stdin);
    freopen("specsort.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j;
    int Max = -1;

    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &A[i]);
        Max = max(Max, A[i]);
    }

    int maxindex = lg2(Max);
    for (i = 0; i <= maxindex; ++i) {
        ones.clear();
        zeroes.clear();
        for (j = 1; j <= N; ++j) {
            if ((A[j] >> i) & 1)
                ones.push_back(A[j]);
            else
                zeroes.push_back(A[j]);
        }
        int pos = 1;
        for (auto it : zeroes)
            A[pos++] = it;
        for (auto it : ones)
            A[pos++] = it;

        for (j = 1; j <= N; ++j) {
            cout << A[j] << ' ';
        }
        cout << '\n';
    }

	return 0;
}
