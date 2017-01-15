#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;
const double eps = 1e-6, PI = acos(-1), inf = 1e100;

int T, N;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
} P[NMAX];

Point Rotate(const Point &P, const double &Cos, const double &Sin) {
    Point ret;
    ret.x = P.x * Cos - P.y * Sin;
    ret.y = P.x * Sin + P.y * Cos;
    return ret;
}

double Check(const double &angle) {
    double min_x = inf, min_y = inf, max_x = -inf, max_y = -inf;
    double Cos = cos(angle), Sin = sin(angle);

    for (int i = 1; i <= N; ++i) {
        Point Rotated = Rotate(P[i], Cos, Sin);

        min_x = min(min_x, Rotated.x);
        min_y = min(min_y, Rotated.y);
        max_x = max(max_x, Rotated.x);
        max_y = max(max_y, Rotated.y);
    }

    return max_x - min_x - max_y + min_y;
}

inline int Sign(const double &value) {
    if (value < -eps)
        return -1;
    if (value > eps)
        return 1;
    return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("tarc.in", "r", stdin) != NULL);
    assert(freopen("tarc.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i;

    cout << fixed;

    for (scanf("%d", &T); T; --T) {
        scanf("%d", &N);
        int x, y;
        for (i = 1; i <= N; ++i) {
            scanf("%d %d", &x, &y);
            P[i] = Point(x, y);
        }

        double left = 0, right = PI / 2, mid;

        for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
            double cleft = Check(left), cmid = Check(mid), cright = Check(right);

            if (Sign(cmid) == 0) {
                break;
            } else if (Sign(cleft) == 0) {
                mid = left;
                break;
            } else if (Sign(cright) == 0) {
                mid = right;
                break;
            }

            if ((Sign(cleft) == -1 && Sign(cmid) == 1) ||
                (Sign(cleft) == 1 && Sign(cmid) == -1)) {
                right = mid;
            } else if ((Sign(cmid) == -1 && Sign(cright) == 1) ||
                       (Sign(cmid) == 1 && Sign(cright) == -1)) {
                left = mid;
            }
        }

        double min_x = inf, min_y = inf, max_x = -inf, max_y = -inf;
        double Cos = cos(mid), Sin = sin(mid);

        for (int i = 1; i <= N; ++i) {
            Point Rotated = Rotate(P[i], Cos, Sin);

            min_x = min(min_x, Rotated.x);
            min_y = min(min_y, Rotated.y);
            max_x = max(max_x, Rotated.x);
            max_y = max(max_y, Rotated.y);
        }

        Point A = Rotate(Point(min_x, min_y), cos(-mid), sin(-mid));
        Point B = Rotate(Point(min_x, max_y), cos(-mid), sin(-mid));
        Point C = Rotate(Point(max_x, min_y), cos(-mid), sin(-mid));
        Point D = Rotate(Point(max_x, max_y), cos(-mid), sin(-mid));

        cout << A.x << ' ' << A.y << '\n' << B.x << ' ' << B.y << '\n' << C.x << ' ' << C.y << '\n' << D.x << ' ' << D.y << '\n';
    }

	return 0;
}
