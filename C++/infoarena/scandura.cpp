#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6 + 10;
typedef int64_t i64;

int N, M;

int main() {
	assert(freopen("scandura.in", "r", stdin));
	assert(freopen("scandura.out", "w", stdout));

	int i;

	scanf("%d %d", &N, &M);
	for (i = 0; i * (M - 1) + 1 < N; ++i);
	int add = i * (M - 1) + 1 - N;
	queue<int> A;
	queue<i64> B;
	while (add--)
		A.push(0);
	for (i = 0; i < N; ++i) {
		int value;
		scanf("%d", &value);
		A.push(value);
	}

	i64 answer = 0;
	while (!A.empty() || !B.empty()) {
		if (A.size() == 0 && B.size() == 1)
			break;
		i64 newnode = 0;
		for (i = 0; i < M; ++i) {
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
		B.push(newnode);
		answer += newnode;
	}

	cout << answer << '\n';
	return 0;
}
