#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300010;

int N, answer;
int line[NMAX];
vector<pair<int, int>> P;

struct Compare {
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const {
        return (lhs.second == rhs.second) ? (lhs.first > rhs.first) : (lhs.second < rhs.second);
    }
};

int GetPos(int value) {
    int left = 1, right = answer, ret = answer + 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (value <= line[mid]) {
            right = mid - 1;
            ret = mid;
        } else
            left = mid + 1;
    }
    return ret;
}

int main() {
    assert(freopen("linii.in", "r", stdin));
    assert(freopen("linii.out", "w", stdout));

    int i;

    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        P.push_back({x - y, x + y});
    }
    sort(P.begin(), P.end(), Compare());
    P.erase(unique(P.begin(), P.end()), P.end());

    for (i = 0; i < int(P.size()); ++i) {
        int pos = GetPos(P[i].first);
        if (pos == answer + 1)
            line[++answer] = P[i].first;
        else
            line[pos] = P[i].first;
    }

    cout << answer << '\n';
    return 0;
}
