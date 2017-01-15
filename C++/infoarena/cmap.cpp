#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef int64_t i64;
typedef pair<int, int> Point;

const int NMAX = 100010;
const i64 inf = 4e18;

int N;
Point X[NMAX], Y[NMAX], aux[NMAX];

inline i64 squareDist(const Point &A, const Point &B) {
	return 1ll * (A.x - B.x) * (A.x - B.x) + 1ll * (A.y - B.y) * (A.y - B.y);
}

struct CompareY {
	bool operator()(const Point &lhs, const Point &rhs) const {
		return lhs.y < rhs.y ? 1 : (lhs.y == rhs.y ? lhs.x < rhs.x : 0);
	}
};

i64 computeMinDist(int left, int right) {
	if (left == right)
		return inf;
	if (right - left == 1) {
		if (Y[left].y > Y[right].y)
			swap(Y[left], Y[right]);
		return squareDist(X[left], X[right]);
	}

	int mid = (left + right) / 2;
	i64 minSqrDist = min(computeMinDist(left, mid), computeMinDist(mid + 1, right));

	merge(Y + left, Y + mid + 1, Y + mid + 1, Y + right + 1, aux, CompareY());
	memcpy(Y + left, aux, (right - left + 1) * sizeof(Point));

	int pos = 0;
	for (int i = left; i <= right; ++i)
		if (1ll * (X[mid].x - Y[i].x) * (X[mid].x - Y[i].x) <= minSqrDist)
			aux[pos++] = Y[i];

	for (int i = 0; i < pos; ++i)
		for (int j = i + 1; j < i + 8 && j < pos; ++j)
			minSqrDist = min(minSqrDist, squareDist(aux[i], aux[j]));

	return minSqrDist;
}

int main() {
	assert(freopen("cmap.in", "r", stdin));
	assert(freopen("cmap.out", "w", stdout));

	int i;

	cin >> N;
	for (i = 1; i <= N; ++i)
		cin >> X[i].x >> X[i].y;
	sort(X + 1, X + N + 1);
	memcpy(Y, X, sizeof Y);

	cout << fixed << setprecision(6) << sqrt(computeMinDist(1, N)) << '\n';

	return 0;
}
