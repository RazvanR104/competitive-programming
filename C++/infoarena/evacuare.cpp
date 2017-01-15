#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair

using namespace std;

const int NMAX = 500010, inf = 0x3f3f3f3f;

int N, M, X;
int ans[NMAX];
vector<pair<int, int>> G[NMAX];
//multiset<pair<int, int>> Q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

int main() {
    ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen("evacuare.in", "r", stdin);
    freopen("evacuare.out", "w", stdout);
    freopen("debug.err", "w", stderr);
    #endif

    int i, j, x, y;

    cin >> N >> M >> X;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        G[x].pb(mp(y, 1));
        G[y].pb(mp(x, 1));
    }

    for (i = 1; i <= N; ++i) {
        cin >> x;
        G[i].pb(mp(x, 0));
    }

    memset(ans, inf, sizeof(ans));
    ans[X] = 0;
    Q.push(mp(0, X));

    while (!Q.empty()) {
        auto now = Q.top();
        Q.pop();

        for (auto i : G[now.second]) {
            if (ans[i.first] > ans[now.second] + i.second) {
                ans[i.first] = ans[now.second] + i.second;
                Q.push(mp(ans[i.first], i.first));
            }
        }
    }

    for (i = 1; i <= N; ++i)
        cout << ans[i] << '\n';

    return 0;
}
