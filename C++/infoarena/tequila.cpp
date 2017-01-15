#include <bits/stdc++.h>

using namespace std;

const int NMAX = 4e6 + 10;

int N, M;
int val[NMAX], level[NMAX];
list<int> G[NMAX];
long double ans;

void DFS(int node) {
	for (const int &it: G[node]) {
		level[it] = level[node] + 1;
		ans += (long double)val[it] / level[it];
		DFS(it);
	}
}

int main() {
	assert(freopen("tequila.in", "r", stdin));
	assert(freopen("tequila.out", "w", stdout));

	int i, j;
	int root = -1;

	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; ++i)
		scanf("%d", &val[i]);
	for (i = 1; i <= N; ++i) {
		int parent;
		scanf("%d", &parent);
		if (parent != -1)
			G[parent].push_back(i);
		else
			root = i;
	}

	level[root] = 1;
	ans = val[root];
	DFS(root);

	cout << fixed;
	cout << ans << '\n';
	while (M--) {
		int x, y;
		scanf("%d %d", &x, &y);
		ans -= (long double)val[x] / level[x];
		val[x] = y;
		ans += (long double)val[x] / level[x];
		cout << ans << '\n';
	}

	return 0;
}
