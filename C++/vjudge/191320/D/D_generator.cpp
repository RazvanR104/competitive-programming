#include <bits/stdc++.h>

using namespace std;

const int VMAX = 1e9, T = 20, NMAX = 100;

int main() {
//	assert(freopen("debug.in", "r", stdin));
	assert(freopen("debug.in", "w", stdout));

	srand(time(0));
	cout << T << '\n';
	for (int j = 0; j < T; ++j) {
		cout << NMAX << ' ' << NMAX << '\n';
		for (int i = 0; i < NMAX; ++i)
			cout << rand() % (VMAX + 1) << ' ';
		cout << '\n';
		for (int i = 0; i < NMAX; ++i) {
			int left = rand() % NMAX + 1;
			int right = NMAX;
			if (left < NMAX)
				right = left + rand() % (NMAX - left + 1);
			cout << left << ' ' << right << ' ' << rand() % (VMAX + 1) << '\n';
		}
	}

	return 0;
}
