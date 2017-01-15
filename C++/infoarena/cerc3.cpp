#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010;

struct Circle {
    int x, y, r;
    Circle(int x = 0, int y = 0, int r = 0): x(x), y(y), r(r) {
    }

    bool operator<(const Circle &rhs) const {
        return (x == rhs.x) ? (y < rhs.y) : (x < rhs.x);
    }
};

bool NotIntersect(const Circle &A, const Circle &B) {
    int cdist = (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);

    if (cdist > (A.r + B.r) * (A.r + B.r))
        return 1;
    return 0;
}

int N, pos;
int DP[NMAX], cnt[NMAX];
vector<Circle> line[NMAX];
map<pair<int, int>, int> where;

int gcd(int x, int y) {
    while (y) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

int main() {
    assert(freopen("cerc3.in", "r", stdin));
    assert(freopen("cerc3.out", "w", stdout));

    int i, j, k, x, y, r;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> x >> y >> r;
        int _gcd = gcd(x, y);
        int rx = x / _gcd;
        int ry = y / _gcd;

        int get = where[{rx, ry}];
        if (get == 0)
            where[{rx, ry}] = get = ++pos;

        line[get].push_back(Circle(x, y, r));
    }

    cout << pos << ' ';
    int answer_2 = 1;
    for (i = 1; i <= pos; ++i) {
        sort(line[i].begin(), line[i].end());
        int curr = 1;
        memset(DP, 0, sizeof DP);
        DP[0] = 1;
        for (j = 1; j < int(line[i].size()); ++j) {
            DP[j] = 1;
            answer_2 = max(answer_2, DP[j]);
            curr = max(curr, DP[j]);
            for (k = j - 1; k >= 0; --k)
                if (NotIntersect(line[i][j], line[i][k])) {
                    DP[j] = max(DP[j], DP[k] + 1);
                    answer_2 = max(answer_2, DP[j]);
                    curr = max(curr, DP[j]);
                }
        }
        ++cnt[curr];
    }
    cout << answer_2 << ' ' << cnt[answer_2] << '\n';

    return 0;
}
