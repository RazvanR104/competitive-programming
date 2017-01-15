#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

#define x first
#define y second

using namespace std;

typedef long long int64;
typedef pair<int, int> Point;

ifstream in("rubarba.in");
ofstream out("rubarba.out");

const int NMAX = 100010, inf = 0x3f3f3f3f;
const long double eps = 1e-4, _max = 1000000000000000LL;

int N, min_x = inf, min_y = inf;
long double a1, b1, c1, a2, b2, c2;

vector<Point> points, convex_hull;

inline int Cross_Product(const Point &A, const Point &B, const Point &C) {
    int64 product = 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x);
    if (product == 0) return 0;
    else if (product > 0) return 1;
    return -1;
}

struct compare {
    bool operator()(const Point &lhs, const Point &rhs) const {
        return (Cross_Product(points[0], lhs, rhs) < 0);
    }
};

inline long double tg(long double x1, long double y1, long double x2, long double y2) {
     if (fabs(x1 - x2) <= eps) return _max;
     return (y1 - y2) / (x1 - x2);
}

void straight_line_eq(const Point &A, const Point &B) {
    long double mid_x = (long double)(A.x + B.x) / 2, mid_y = (long double)(A.y + B.y) / 2;

    a1 = tg(A.x, A.y, B.x, B.y);
    if (fabs(a1) <= eps) a2 = -_max;
    else a2 = -1 / a1;
    b1 = b2 = -1;
    c1 = A.y - A.x * a1;
    c2 = mid_y - mid_x * a2;
}

long double Distance(const Point &P, const long double &a, const long double &b, const long double &c) {
    return ((a * P.x + b * P.y + c) / sqrtl(a * a + b * b));
}

long double labs(const long double &value) {
    if (value < 0) return -value;
    return value;
}

int main() {
    freopen("rubarba.out", "w", stdout);
    int i, x, y, pos = 0;

    in >> N;

    for (i = 0; i < N; ++i) {
        in >> x >> y;
        points.push_back(make_pair(x, y));

        if (min_y > y || (min_y == y && min_x > x)) min_x = x, min_y = y, pos = i;
    }

    swap(points[0], points[pos]);
    sort(points.begin() + 1, points.end(), compare());

    convex_hull.push_back(points[0]), convex_hull.push_back(points[1]);

    for (i = 2; i < N; ++i) {
        int product = Cross_Product(convex_hull[convex_hull.size() - 2], convex_hull[convex_hull.size() - 1], points[i]);

        if (product == 0) convex_hull.pop_back();
        else if (product > 0) {
            while (product >= 0 && convex_hull.size() > 2) {
                convex_hull.pop_back();
                product = Cross_Product(convex_hull[convex_hull.size() - 2], convex_hull[convex_hull.size() - 1], points[i]);
            }
        }
        convex_hull.push_back(points[i]);
    }

    convex_hull.push_back(convex_hull.front());

    if (convex_hull.size() < 4) {
        out << "0.00\n";
        return 0;
    }

    long double res = _max, A, B, C;
    for (size_t it = 0; it < convex_hull.size() - 1; ++it) {
        straight_line_eq(convex_hull[it], convex_hull[it + 1]);

        A = B = C = 0;

        for (size_t _it = 0; _it < convex_hull.size(); ++_it) {
            A = max(A, labs(Distance(convex_hull[_it], a1, b1, c1)));
            B = max(B, Distance(convex_hull[_it], a2, b2, c2));
            C = min(C, Distance(convex_hull[_it], a2, b2, c2));
        }

        res = min(res, (B - C) * A);
    }

    printf("%.2llf\n", res);

    in.close(), out.close();
    return 0;
}
