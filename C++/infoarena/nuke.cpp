#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010, MMAX = 100010;

struct Point {
    int x, y, r;

    Point(int x = 0, int y = 0, int r = 0) : x(x), y(y), r(r) {}

    bool operator<(const Point &rhs) const {
        if (x < rhs.x)
            return 1;
        if (x > rhs.x)
            return 0;
        if (y < rhs.y)
            return 1;
        return 0;
    }
} P[NMAX], NU[MMAX];

struct Event {
    int time, pos, op;

    Event(int time = 0, int pos = 0, int op = 0) : time(time), pos(pos), op(op) {}

    bool operator<(const Event &rhs) const {
        return time < rhs.time;
    }
} E[2 * MMAX];

struct Node {
    int y, pos;
    Node(int y = 0, int pos = 0) : y(y), pos(pos) {}

    bool operator<(const Node &rhs) const {
        return y < rhs.y;
    }
    bool operator<(const int &rhs) const {
        return y < rhs;
    }
};

int N, M;
int answer[MMAX];
set<Node> C;

bool Check(Point Circle, Point P) {
    return (1ll * (Circle.x - P.x) * (Circle.x - P.x) + 1ll * (Circle.y - P.y) * (Circle.y - P.y) <= 1ll * Circle.r * Circle.r);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("nuke.in", "r", stdin) != NULL);
    assert(freopen("nuke.out", "w", stdout) != NULL);
    //assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> N >> M;

    int i, j, x, y, r;

    for (i = 1; i <= N; ++i) {
        cin >> x >> y;
        P[i] = Point(x, y, -1);
    }
    sort(P + 1, P + N + 1);

    for (i = 1; i <= M; ++i) {
        cin >> x >> y >> r;
        NU[i] = Point(x, y, r);
    }

    int pos = 0;
    for (i = 1; i <= M; ++i) {
        E[++pos] = Event(NU[i].x - NU[i].r, i, 1);
        E[++pos] = Event(NU[i].x + NU[i].r + 1, i, -1);
    }
    sort(E + 1, E + pos + 1);

    j = 1;
    for (i = 1; i <= N; ++i) {
        while (j <= pos && P[i].x >= E[j].time) {
            if (E[j].op == 1) {
                C.insert(Node(NU[E[j].pos].y, E[j].pos));
            }
            else
                C.erase(Node(NU[E[j].pos].y, E[j].pos));
            ++j;
        }

        auto it = C.lower_bound(P[i].y);
        if (it != C.end())
            if (Check(NU[it->pos], P[i]))
                ++answer[it->pos];

        if (it != C.begin()) {
            --it;
            if (Check(NU[it->pos], P[i]))
                ++answer[it->pos];
        }
    }

    for (i = 1; i <= M; ++i)
        cout << answer[i] << '\n';

	return 0;
}
