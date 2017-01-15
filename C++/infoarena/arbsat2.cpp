#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int BASE = 100000001;

int N, M;
unordered_set<i64> already;
vector<pair<int, int>> points, new_points;

void solve(int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    for (int i = left; i <= right; ++i) {
        int new_x = points[mid].first;
        int new_y = points[i].second;
        i64 hash = i64(new_x) * BASE + new_y;

        if (already.count(hash))
            continue;

        already.insert(hash);
        new_points.push_back({new_x, new_y});
    }

    solve(left, mid - 1);
    solve(mid + 1, right);
}

int main() {
    assert(freopen("arbsat2.in", "r", stdin));
    assert(freopen("arbsat2.out", "w", stdout));

    int i;
    int x, y;

    scanf("%d %d", &N, &M);
    for (i = 0; i < N; ++i) {
        scanf("%d %d", &x, &y);
        already.insert(i64(x) * BASE + y);
        points.push_back({x, y});
    }

    sort(points.begin(), points.end());
    solve(0, N - 1);

    cout << new_points.size() << '\n';
    for (const auto &it: new_points)
        cout << it.first << ' ' << it.second << '\n';

    return 0;
}
