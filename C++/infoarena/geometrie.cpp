#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

const int NMAX = 100010;
typedef int64_t i64;
typedef pair<int, int> Point;

int N, M;
double answer[NMAX];
i64 le_area[NMAX], ue_area[NMAX];
pair<int, int> P[NMAX];
vector<pair<int, int>> lower_envelope, upper_envelope;

struct Query {
    int x, y, pos;

    bool operator <(const Query &rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }

    Point get() {
        return {x, y};
    }
} Q[NMAX];

i64 Area(const Point &A, const Point &B, const Point &C) {
    return i64(B.x - A.x) * (C.y - A.y) - i64(C.x - A.x) * (B.y - A.y);
}

void NewPoint(const Point &now) {
    while (upper_envelope.size() >= 2 && Area(upper_envelope[upper_envelope.size() - 2], upper_envelope[upper_envelope.size() - 1], now) >= 0)
        upper_envelope.pop_back();
    upper_envelope.push_back(now);

    if (upper_envelope.size() >= 2)
        ue_area[upper_envelope.size()] = ue_area[upper_envelope.size() - 1] + Area({0, 0}, upper_envelope[upper_envelope.size() - 1], upper_envelope[upper_envelope.size() - 2]);

    while (lower_envelope.size() >= 2 && Area(lower_envelope[lower_envelope.size() - 2], lower_envelope[lower_envelope.size() - 1], now) <= 0)
        lower_envelope.pop_back();
    lower_envelope.push_back(now);

    if (lower_envelope.size() >= 2)
        le_area[lower_envelope.size()] = le_area[lower_envelope.size() - 1] + Area({0, 0}, lower_envelope[lower_envelope.size() - 2], lower_envelope[lower_envelope.size() - 1]);
}

int main() {
    assert(freopen("geometrie.in", "r", stdin));
    assert(freopen("geometrie.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i)
        scanf("%d %d", &P[i].x, &P[i].y);
    sort(P + 1, P + N + 1);

    for (i = 1; i <= M; ++i) {
        scanf("%d %d", &Q[i].x, &Q[i].y);
        Q[i].pos = i;
    }
    sort(Q + 1, Q + M + 1);

    int now = 1;
    for (i = 1; i <= M; ++i) {
        while (now <= N && P[now].x < Q[i].x)
            NewPoint(P[now++]);

        int left = 0, right = lower_envelope.size() - 2, mid, le_index = -1;
        while (left <= right) {
            mid = (left + right) >> 1;
            if (Area(lower_envelope[mid], lower_envelope[mid + 1], Q[i].get()) > 0)
                left = mid + 1;
            else {
                right = mid - 1;
                le_index = mid;
            }

        }

        left = 0, right = upper_envelope.size() - 2;
        int ue_index = -1;
        while (left <= right) {
            mid = (left + right) >> 1;
            if (Area(upper_envelope[mid], upper_envelope[mid + 1], Q[i].get()) < 0)
                left = mid + 1;
            else {
                right = mid - 1;
                ue_index = mid;
            }

        }

        if (lower_envelope.size() != 0) {
            if (le_index == -1)
                answer[Q[i].pos] += le_area[lower_envelope.size()] + Area({0, 0}, lower_envelope.back(), Q[i].get());
            else
                answer[Q[i].pos] += le_area[le_index + 1] + Area({0, 0}, lower_envelope[le_index], Q[i].get());
        }

        if (upper_envelope.size() != 0) {
            if (ue_index == -1)
                answer[Q[i].pos] += ue_area[upper_envelope.size()] + Area({0, 0}, Q[i].get(), upper_envelope.back());
            else
                answer[Q[i].pos] += ue_area[ue_index + 1] + Area({0, 0}, Q[i].get(), upper_envelope[ue_index]);
        }
    }

    cout << fixed << setprecision(1);
    for (i = 1; i <= M; ++i)
        cout << answer[i] / 2 << '\n';

    return 0;
}
