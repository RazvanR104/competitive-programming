#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

typedef int64_t i64;

const int NMAX = 50010;
const long double PI = acos(double(-1));

int N, X, Y;
double A[NMAX];

struct Point {
    int x, y;
    double a;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {
        a = atan2(double(_y), double(_x)) * 180 / PI;
        if (a < 0)
            a = 360 + a;
    }

    bool operator<(const Point &rhs) const {
        return a < rhs.a;
    }
} P[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("hawaii.in", "r", stdin);
    freopen("hawaii.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j, x, y;

    scanf("%d %d %d", &N, &X, &Y);

    i64 total = i64(N) * (N - 1) * (N - 2) / 6;

    for (i = 1; i <= N; ++i) {
        scanf("%d %d", &x, &y);
        P[i] = Point(x - X, y - Y);
    }
    sort(P + 1, P + N + 1);

    for (i = 1; i <= N; ++i) {
        A[i] = atan2(double(P[i].y), double(P[i].x)) * 180 / PI;
        if (A[i] < 0)
            A[i] = 360 + A[i];
    }

    i64 substract = 0;

    for (i = 1; i <= N; ++i) {
        double a = A[i];
        double finish = a + 180;
        if (finish > 360)
            finish -= 360;
        //int pos = lower_bound(A + 1, A + N + 1, finish) - A;
        int pos = 0;
        for (int bit = 15; bit >= 0; --bit) {
            if ((pos | (1 << bit)) <= N && finish >= A[pos | (1 << bit)])
                pos |= (1 << bit);
        }
        ++pos;

        if (i < pos) {
            int lol = pos - i - 1;
            substract += (lol) * (lol - 1) / 2;
        } else if (i > pos) {
            int lol = pos - 1 + N - i;
            substract += (lol) * (lol - 1) / 2;
        }
    }

    cout << total - substract << '\n';

	return 0;
}
