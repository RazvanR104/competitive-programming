#include <bits/stdc++.h>

using namespace std;

int N, M, K;
vector<pair<int, int>> G[2], answer;

class DisjointSet {
	public:
		DisjointSet(int size):
			size(size),
			Set(new int[size]),
			Height(new int[size]()) {
			for (int i = 0; i < size; ++i)
				Set[i] = i;
		}

		bool doUnion(int node1, int node2) {
			int root1 = getRoot(node1);
			int root2 = getRoot(node2);

			if (root1 == root2)
				return false;

			if (Height[root1] > Height[root2])
				Set[root2] = root1;
			else if (Height[root1] < Height[root2])
				Set[root1] = root2;
			else {
				Set[root2] = root1;
				++Height[root1];
			}

			return true;
		}

		bool sameSet(int node1, int node2) {
			return getRoot(node1) != getRoot(node2);
		}

	private:
		int size;
		int *Set, *Height;

		int getRoot(int node) {
			int root = node;
			while (root != Set[root])
				root = Set[root];

			int father;
			while (node != Set[node]) {
				father = Set[node];
				Set[node] = root;
				node = father;
			}

			return root;
		}
};

int main() {
	assert(freopen("karb.in", "r", stdin));
	assert(freopen("karb.out", "w", stdout));

	scanf("%d %d %d", &N, &M, &K);
	int x, y, w;
	while (M--) {
		scanf("%d %d %d", &x, &y, &w);
		G[w].push_back({x, y});
	}

	DisjointSet *DS1 = new DisjointSet(N);
	DisjointSet *DS2 = new DisjointSet(N);
	for (const auto &it: G[0])
		DS1->doUnion(it.first - 1, it.second - 1);

	for (const auto &it: G[1])
		if (DS1->doUnion(it.first - 1, it.second - 1))
			answer.push_back(it);

	for (const auto &it: answer)
		DS2->doUnion(it.first - 1, it.second - 1);

	int current_size = answer.size();
	for (const auto &it: G[1]) {
		if (current_size >= K)
			break;
		if (DS2->doUnion(it.first - 1, it.second - 1)) {
			answer.push_back(it);
			++current_size;
		}
	}

	for (const auto &it: G[0])
		if (DS2->doUnion(it.first - 1, it.second - 1))
			answer.push_back(it);

	for (const auto &it: answer)
		cout << it.first << ' ' << it.second << '\n';

	return 0;
}
