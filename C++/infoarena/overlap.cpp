#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int NMAX = 810, CMAX = 100010;

unordered_map<i64, int> H;

const int Cos[] = {1, 0, -1, 0};
const int Sin[] = {0, 1, 0, -1};

int N;
int Next[NMAX], answer[NMAX];
bool seen[NMAX], in[NMAX];

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    void Rotate(int k) {
        int _x = x * Cos[k] - y * Sin[k];
        int _y = x * Sin[k] + y * Cos[k];
        x = _x, y = _y;
    }

    void Shift(int shift_x, int shift_y) {
        x += shift_x;
        y += shift_y;
    }
} P[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("overlap.in", "r", stdin) != NULL);
    assert(freopen("overlap.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, k, x, y;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> x >> y;
        P[i] = Point(x, y);
        i64 key = 1ll * x * CMAX + y;
        H[key] = i;
    }

    for (i = 0; i < 4; ++i) {
        Point Ref = P[1];
        Ref.Rotate(i);

        int shift_x, shift_y;
        for (j = 2; j <= N; ++j) {
            shift_x = P[j].x - Ref.x;
            shift_y = P[j].y - Ref.y;

            memset(in, 0, sizeof(in));
            for (k = 1; k <= N; ++k) {
                Point now = P[k];
                now.Rotate(i);
                now.Shift(shift_x, shift_y);

                i64 key = 1ll * now.x * CMAX + now.y;
                if (H.count(key)) {
                    Next[k] = H[key];
                    in[Next[k]] = 1;
                }
                else
                    Next[k] = 0;
            }

            memset(seen, 0, sizeof(seen));
            seen[0] = 1;
            for (k = 1; k <= N; ++k) {
                if (in[k])
                    continue;
                int now = k, mark = 0;

                int count = 0;
                while (seen[now] == 0) {
                    seen[now] = 1;
                    answer[now] = mark;
                    mark ^= 1;
                    now = Next[now];
                    ++count;
                }

                if (count % 2)
                    goto OUT;
            }

            for (k = 1; k <= N; ++k) {
                if (seen[k])
                    continue;
                int now = k, mark = 0;

                int count = 0;
                while (seen[now] == 0) {
                    seen[now] = 1;
                    answer[now] = mark;
                    mark ^= 1;
                    now = Next[now];
                    ++count;
                }

                if (count % 2)
                    goto OUT;
            }

            for (k = 1; k <= N; ++k)
                cout << answer[k] + 1 << '\n';
            return 0;

            OUT:;
        }
    }

	return 0;
}
