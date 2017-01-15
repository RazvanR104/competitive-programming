#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010, LG2NMAX = 19;

int N, K;
int level[NMAX], color[NMAX], cnt[NMAX];
int LCA[LG2NMAX][2 * NMAX], pos, first[NMAX];
int disjoint[NMAX], height[NMAX], setsize[NMAX];
int64_t answer[NMAX];
vector<int> T[NMAX], order[NMAX];

void DFS(int node, int father, int curr_level) {
	level[node] = curr_level;
	LCA[0][++pos] = node;
	first[node] = pos;
	for (const int &it: T[node]) {
		if (it == father)
			continue;
		DFS(it, node, curr_level + 1);
		LCA[0][++pos] = node;
	}
	order[color[node]].push_back(node);
}

int floorLg2(int value) {
	int answer = 0;
	for (int bit = 16; bit; bit >>= 1)
		if (value >> (answer + bit))
			answer += bit;
	return answer;
}

void preprocessLCA() {
	for (int i = 1; (1 << i) <= pos; ++i)
		for (int j = 1; j + (1 << i) - 1 <= pos; ++j)
			LCA[i][j] = level[LCA[i - 1][j]] < level[LCA[i - 1][j + (1 << (i - 1))]] ? LCA[i - 1][j] : LCA[i - 1][j + (1 << (i - 1))];
}

int getLCA(int node1, int node2) {
	if (first[node1] > first[node2])
		swap(node1, node2);
	int lgdist = floorLg2(first[node2] - first[node1] + 1);
	return level[LCA[lgdist][first[node1]]] < level[LCA[lgdist][first[node2] - (1 << lgdist) + 1]] ? LCA[lgdist][first[node1]] : LCA[lgdist][first[node2] - (1 << lgdist) + 1];
}

int getRoot(int node) {
	int root = node;
	while (disjoint[root] != root)
		root = disjoint[root];
	int _node = node;
	while (disjoint[node] != node) {
		_node = disjoint[node];
		disjoint[node] = root;
		node = _node;
	}
	return root;
}

int doUnion(int node1, int node2) {
	int root1 = getRoot(node1);
	int root2 = getRoot(node2);
	if (root1 == root2)
		return 0;
	if (height[root1] > height[root2]) {
		disjoint[root2] = root1;
		setsize[root1] += setsize[root2];
		return root1;
	} else if (height[root1] < height[root2]) {
		disjoint[root1] = root2;
		setsize[root2] += setsize[root1];
		return root2;
	} else {
		disjoint[root2] = root1;
		setsize[root1] += setsize[root2];
		++height[root1];
		return root1;
	}
}

int main() {
	assert(freopen("kdist.in", "r", stdin));
	assert(freopen("kdist.out", "w", stdout));

	int i, j;

	scanf("%d %d", &N, &K);
	for (i = 0; i < N - 1; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		T[x].push_back(y);
		T[y].push_back(x);
	}

	for (i = 1; i <= N; ++i) {
		scanf("%d", &color[i]);
		++cnt[color[i]];
	}

	DFS(1, -1, 1);
	preprocessLCA();

	for (i = 1; i <= N; ++i) {
		disjoint[i] = i;
		setsize[i] = 1;
	}

	for (i = 1; i <= N; ++i)
		answer[color[i]] += int64_t(level[i]) * (cnt[color[i]] - 1);

	for (i = 1; i <= K; ++i) {
		vector<tuple<int, int, int, int>> LCAs;
		for (j = 1; j < int(order[i].size()); ++j) {
			int LCA = getLCA(order[i][j - 1], order[i][j]);
			LCAs.push_back(make_tuple(level[LCA], LCA, order[i][j - 1], order[i][j]));
		}
		sort(LCAs.begin(), LCAs.end(), greater<tuple<int, int, int, int>>());
		for (const auto &it: LCAs) {
				int level, lca, x, y;
				tie(level, lca, x, y) = it;
				int root1 = getRoot(x);
				int root2 = getRoot(y);
				answer[i] -= 2 * int64_t(level) * int64_t(setsize[root1]) * int64_t(setsize[root2]);
				doUnion(root1, root2);
		}

		cout << answer[i] << '\n';
	}

	return 0;
}
