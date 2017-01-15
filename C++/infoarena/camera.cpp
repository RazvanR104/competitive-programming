#include <bits/stdc++.h>

#define sz(x) (int(x.size()))
#define pb push_back

using namespace std;

const int NMAX = 2010;
const double eps = 1e-6, inf = 1e32;

int N;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

struct Line {
    double a, b, c;
    Line() {}
    Line(const Point &A, const Point &B) {
        a = -(B.y - A.y);
        b = -(A.x - B.x);
        c = -(B.x * A.y - A.x * B.y);
    }
};

Point Intersect(const Line &A, const Line &B) {
    double num = B.a * A.b - A.a * B.b;
    double x = (B.b * A.c - A.b * B.c) / num;
    double y = (A.a * B.c - B.a * A.c) / num;
    return Point(x, y);
}

double Pos(const Line &L, const Point &P) {
    return L.a * P.x + L.b * P.y + L.c;
}

double Det(const Point &A, const Point &B) {
    return A.x * B.y - B.x * A.y;
}

double Area(const vector<Point> &V) {
    double res = 0;
    for (int i = 0; i < sz(V) - 1; ++i)
        res += Det(V[i], V[i + 1]);
    return res / 2;
}

vector<Point> P;

vector<Point> Current;

void Process(const Line &L) {
    for (int i = 0; i < sz(Current) - 1; ++i) {
        if (Pos(L, Current[i]) * Pos(L, Current[i + 1]) <= -eps) {
            Current.insert(Current.begin() + i + 1, Intersect(L, Line(Current[i], Current[i + 1])));
            ++i;
        }
    }

    vector<Point> New;
    for (int i = 0; i < sz(Current) - 1; ++i) {
        if (Pos(L, Current[i]) >= -eps)
            New.pb(Current[i]);
    }

    if (sz(New))
        New.push_back(New[0]);

    Current = New;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("camera.in", "r", stdin);
    freopen("camera.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, x, y;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> x >> y;
        P.pb(Point(x, y));
    }
    P.pb(P[0]);

    if (Area(P) < 0)
        reverse(P.begin(), P.end());

    double minx = inf, maxx = -inf, miny = inf, maxy = -inf;

    for (i = 0; i < sz(P); ++i) {
        minx = min(minx, P[i].x);
        miny = min(miny, P[i].y);
        maxx = max(maxx, P[i].x);
        maxy = max(maxy, P[i].y);
    }

    Current.pb(Point(minx, maxy));
    Current.pb(Point(minx, miny));
    Current.pb(Point(maxx, miny));
    Current.pb(Point(maxx, maxy));
    Current.pb(Point(minx, maxy));

    for (i = 0; i < sz(P) - 1; ++i)
        Process(Line(P[i], P[i + 1]));

    cout << fixed << setprecision(2) << Area(Current) << '\n';

	return 0;
}
