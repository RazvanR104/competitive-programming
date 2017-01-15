#include <bits/stdc++.h>

using namespace std;

const int NMAX = 710;

int N, M;
char V[NMAX][NMAX];
short goDown[NMAX][NMAX], goUp[NMAX][NMAX], goLeft[NMAX][NMAX], goRight[NMAX][NMAX];
short A[NMAX][NMAX], B[NMAX][NMAX];

int splitLeftRight(int x1, int y1, int x2, int y2) {
	int mid = (y1 + y2) / 2;
	int answer = 0;
	int i, j;

	for (i = x1; i <= x2; ++i) {
		int left = goLeft[i][mid] >= y1 ? goLeft[i][mid] : y1;
		int right = goRight[i][mid + 1] <= y2 ? goRight[i][mid + 1] : y2;
		left = goLeft[i][mid] == 0 ? 0 : left;
		right = goRight[i][mid + 1] == 0 ? 0 : right;
		for (j = i; j <= x2; ++j) {
			if (V[i][left] == 0) {
				A[i][j] = 0;
			} else {
				while (left + 1 <= mid && goDown[i][left] < j)
					++left;
				A[i][j] = goDown[i][left] >= j ? left : 0;
			}

			if (V[i][right] == 0) {
				B[i][j] = 0;
			} else {
				while (right - 1 > mid && goDown[i][right] < j)
					--right;
				B[i][j] = goDown[i][right] >= j ? right : 0;
			}
		}
	}

	for (i = x2; i >= x1; --i) {
		int left = goLeft[i][mid] >= y1 ? goLeft[i][mid] : y1;
		int right = goRight[i][mid + 1] <= y2 ? goRight[i][mid + 1] : y2;
		left = goLeft[i][mid] == 0 ? 0 : left;
		right = goRight[i][mid + 1] == 0 ? 0 : right;
		for (j = i; j >= x1; --j) {
			if (V[i][left] == 0) {
				A[i][j] = 0;
			} else {
				while (left + 1 <= mid && goUp[i][left] > j)
					++left;
				A[i][j] = goUp[i][left] <= j ? left : 0;
			}

			if (V[i][right] == 0) {
				B[i][j] = 0;
			} else {
				while (right - 1 > mid && goUp[i][right] > j)
					--right;
				B[i][j] = goUp[i][right] <= j ? right : 0;
			}
		}
	}

	for (i = x1; i <= x2; ++i) {
		for (j = i; j <= x2; ++j) {
			if (A[i][j] == 0 || A[j][i] == 0 || B[i][j] == 0 || B[j][i] == 0)
				continue;
			answer = max(answer, (min(B[i][j], B[j][i]) - max(A[i][j], A[j][i]) + 1) * (j - i + 1));
		}
	}

	return answer;
}

int splitTopBottom(int x1, int y1, int x2, int y2) {
	int mid = (x1 + x2) / 2;
	int answer = 0;
	int i, j;

	for (i = y1; i <= y2; ++i) {
		int top = goUp[mid][i] >= x1 ? goUp[mid][i] : x1;
		int bottom = goDown[mid + 1][i] <= x2 ? goDown[mid + 1][i] : x2;
		top = goUp[mid][i] == 0 ? 0 : top;
		bottom = goDown[mid + 1][i] == 0 ? 0 : bottom;
		for (j = i; j <= y2; ++j) {
			if (V[top][i] == 0) {
				A[i][j] = 0;
			} else {
				while (top + 1 <= mid && goRight[top][i] < j)
					++top;
				A[i][j] = goRight[top][i] >= j ? top : 0;
			}
			if (V[bottom][i] == 0) {
				B[i][j] = 0;
			} else {
				while (bottom - 1 > mid && goRight[bottom][i] < j)
					--bottom;
				B[i][j] = goRight[bottom][i] >= j ? bottom : 0;
			}
		}
	}

	for (i = y2; i >= y1; --i) {
		int top = goUp[mid][i] >= x1 ? goUp[mid][i] : x1;
		int bottom = goDown[mid + 1][i] <= x2 ? goDown[mid + 1][i] : x2;
		top = goUp[mid][i] == 0 ? 0 : top;
		bottom = goDown[mid + 1][i] == 0 ? 0 : bottom;
		for (j = i; j >= y1; --j) {
			if (V[top][i] == 0) {
				A[i][j] = 0;
			} else {
				while (top + 1 <= mid && goLeft[top][i] > j)
					++top;
				A[i][j] = goLeft[top][i] <= j ? top : 0;
			}
			if (V[bottom][i] == 0) {
				B[i][j] = 0;
			} else {
				while (bottom - 1 > mid && goLeft[bottom][i] > j)
					--bottom;
				B[i][j] = goLeft[bottom][i] <= j ? bottom : 0;
			}
		}
	}

	for (i = y1; i <= y2; ++i) {
		for (j = i; j <= y2; ++j) {
			if (A[i][j] == 0 || A[j][i] == 0 || B[i][j] == 0 || B[j][i] == 0)
				continue;
			answer = max(answer, (min(B[i][j], B[j][i]) - max(A[i][j], A[j][i]) + 1) * (j - i + 1));
		}
	}

	return answer;
}

int solve(int x1, int y1, int x2, int y2) {
	/*if (x1 == x2 && y1 == y2)
		return V[x1][y1];

	int answer = 0;
	int mid;
	if (y2 - y1 > x2 - x1) {
		mid = (y1 + y2) / 2;
		answer = max(answer, solve(x1, y1, x2, mid));
		answer = max(answer, solve(x1, mid + 1, x2, y2));
		answer = max(answer, splitLeftRight(x1, y1, x2, y2));
	} else {
		mid = (x1 + x2) / 2;
		answer = max(answer, solve(x1, y1, mid, y2));
		answer = max(answer, solve(mid + 1, y1, x2, y2));
		answer = max(answer, splitTopBottom(x1, y1, x2, y2));
	}
	return answer;*/

	if (y1 == y2) {
        int answer = 0, curr = 0;
        for (int i = x1; i <= x2; ++i) {
            if (V[i][y1] == 0)
                curr = 0;
            else
                answer = max(answer, ++curr);
        }
        return answer;
    }

    int mid = (y1 + y2) / 2;
    int answer = 0;
    answer = max(answer, solve(x1, y1, x2, mid));
    answer = max(answer, solve(x1, mid + 1, x2, y2));
    answer = max(answer, splitLeftRight(x1, y1, x2, y2));
    return answer;
}

int main() {
	assert(freopen("rama.in", "r", stdin));
	assert(freopen("rama.out", "w", stdout));

	int i, j;

	cin >> N >> M;
	cin.ignore();
	for (i = 1; i <= N; ++i) {
		cin.getline(V[i] + 1, NMAX);
		for (j = 1; j <= M; ++j)
			V[i][j] -= '0';
	}

	for (j = 1; j <= M; ++j) {
		for (i = N; i >= 1; ) {
			if (V[i][j]) {
				int initial = i;
				while (V[i][j])
					goDown[i--][j] = initial;
			} else
				--i;
		}
	}

	for (j = 1; j <= M; ++j) {
		for (i = 1; i <= N; ) {
			if (V[i][j]) {
				int initial = i;
				while (V[i][j])
					goUp[i++][j] = initial;
			} else
				++i;
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = M; j >= 1; ) {
			if (V[i][j]) {
				int initial = j;
				while (V[i][j])
					goRight[i][j--] = initial;
			} else
				--j;
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= M; ) {
			if (V[i][j]) {
				int initial = j;
				while (V[i][j])
					goLeft[i][j++] = initial;
			} else
				++j;
		}
	}

	cout << solve(1, 1, N, M) << '\n';

	return 0;
}
