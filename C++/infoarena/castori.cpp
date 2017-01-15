#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10010;
const double eps = 1e-8, sqrt2 = sqrt(2);

int N, C;
int ST[2][8 * NMAX];
double X[NMAX], Y[NMAX];

void updateTree(int node, int left, int right, int qleft, int qright, int value) {
    if (left >= qleft && right <= qright) {
        ST[0][node] += value;
        ST[1][node] += value;
        return;
    }
    if (left == right)
        return;
    int mid = (left + right) / 2;
    if (qleft <= mid)
        updateTree(node * 2, left, mid, qleft, qright, value);
    if (qright > mid)
        updateTree(node * 2 + 1, mid + 1, right, qleft, qright, value);

		ST[1][node] = ST[0][node] + max(ST[1][node * 2], ST[1][node * 2 + 1]);
}

struct Event {
    double x, y1, y2;
    int pos1, pos2;
    Event(double x, double y1, double y2):
        x(x),
        y1(y1),
        y2(y2) {
    }
    bool operator<(const Event &rhs) const {
        double diff = x - rhs.x;
        return diff >= -eps && diff <= eps ? 0 : (diff < -eps ? 1 : 0);
    }
};

struct Comparator {
    bool operator()(const double &lhs, const double &rhs) const {
        double diff = lhs - rhs;
        return diff >= -eps && diff <= eps ? 0 : (diff < -eps ? 1 : 0);
    }
};

bool checkDistance(int D) {
    memset(ST, 0, sizeof ST);
    vector<Event> add, del;
    vector<double> P;

    double length = D / (2 * sqrt2);
    for (int i = 1; i <= N; ++i) {
        add.push_back(Event(X[i] - length, Y[i] - length, Y[i] + length));
        del.push_back(Event(X[i] + length, Y[i] - length, Y[i] + length));
        P.push_back(Y[i] - length);
        P.push_back(Y[i] + length);
    }

    sort(P.begin(), P.end(), Comparator());
    int it1 = 0, it2 = 0;
    for (it1 = 0; it1 < int(add.size()); ++it1) {
			add[it1].pos1 = del[it1].pos1 = lower_bound(P.begin(), P.end(), add[it1].y1, Comparator()) - P.begin() + 1;
			add[it1].pos2 = del[it1].pos2 = upper_bound(P.begin(), P.end(), add[it1].y2, Comparator()) - P.begin();
    }
    sort(add.begin(), add.end());
    sort(del.begin(), del.end());

    for (it1 = 0; it1 < int(add.size()); ++it1) {
        while (it2 < int(del.size()) && add[it1].x - del[it2].x > eps) {
            updateTree(1, 1, P.size(), del[it2].pos1, del[it2].pos2, -1);
            ++it2;
        }
        updateTree(1, 1, P.size(), add[it1].pos1, add[it1].pos2, 1);
        if (ST[1][1] >= C)
            return 1;
    }

    return 0;
}

int main() {
    assert(freopen("castori.in", "r", stdin));
    assert(freopen("castori.out", "w", stdout));

    int i;

    scanf("%d %d", &N, &C);
    for (i = 1; i <= N; ++i) {
        double x, y;
        scanf("%lf %lf", &x, &y);
        X[i] = (x - y) * sqrt2 / 2;
        Y[i] = (x + y) * sqrt2 / 2;
    }

    int answer = 0;
    for (int bit = (1 << 30); bit; bit >>= 1)
        if (!checkDistance(answer + bit))
            answer += bit;

    cout << answer + 1 << '\n';

    return 0;
}
