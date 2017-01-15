#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6 + 10;
typedef int64_t i64;

int N;
int V[NMAX];

int main() {
	assert(freopen("k1.in", "r", stdin));
	assert(freopen("k1.out", "w", stdout));

	int i;
	scanf("%d", &N);
	for (i = 0; i < N; ++i)
		scanf("%d", &V[i]);
	sort(V, V + N);

	queue<int> A;
	queue<i64> B;
	for (i = 0; i < N; ++i)
		A.push(V[i]);

	i64 answer = 0;
	while (!A.empty() || !B.empty()) {
		if (A.size() == 0 && B.size() == 1)
			break;
		i64 newnode = 0;
		for (i = 0; i < 2; ++i) {
			if (!A.empty() && !B.empty()) {
				if (A.front() < B.front()) {
					newnode += A.front();
					A.pop();
				} else {
					newnode += B.front();
					B.pop();
				}
			} else if (!A.empty()) {
				newnode += A.front();
				A.pop();
			} else {
				newnode += B.front();
				B.pop();
			}
		}
		answer += newnode;
		B.push(newnode);
	}

	cout << answer << '\n';
	return 0;
}
