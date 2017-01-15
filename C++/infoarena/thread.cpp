#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300;

int T, N;
bool sum[NMAX * NMAX];
int values[NMAX * NMAX], add[NMAX * NMAX];

void generateTest() {
	ofstream cout("thread.in");
	const int T = 128, N = 256, MOD = 257;
	srand(time(0));
	cout << T << '\n';
	for (int i = 0; i < T; ++i) {
		cout << N << '\n';
		for (int j = 0; j < N; ++j)
			cout << rand() % MOD << ' ';
		cout << '\n';
	}
	cout.close();
	exit(0);
}

int main() {
    assert(freopen("thread.in", "r", stdin));
    assert(freopen("thread.out", "w", stdout));

//		generateTest();

    for (cin >> T; T; --T) {
    	memset(sum, 0, sizeof sum);
    	int i, j;
    	cin >> N;
    	bool zero = 0;
    	values[0] = 0;
    	values[++values[0]] = 0;
    	sum[0] = 1;
    	for (i = 0; i < N; ++i) {
	    	int value;
	    	cin >> value;
	    	if (value == 0)
	    		zero = 1;
				add[0] = 0;
				for (j = 1; j <= values[0]; ++j)
					if (sum[values[j] + value] == 0)
						add[++add[0]] = values[j] + value;
				for (j = 1; j <= add[0]; ++j) {
					sum[add[j]] = 1;
					values[++values[0]] = add[j];
				}
    	}
    	if (!zero)
				cout << values[0] - 1 << '\n';
			else
				cout << values[0] << '\n';
    }

    return 0;
}
