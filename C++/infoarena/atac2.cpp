#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10010, UMAX = 80, inf = 0x3f3f3f3f;

struct Edge {
    int from, to, cap, cost, flow;
    Edge *rev;

    Edge(int from, int to, int cap, int cost):
        from(from),
        to(to),
        cap(cap),
        cost(cost),
        flow(0),
        rev(0) {
    }
};

int N, M, U, X;
int u[2 * UMAX + 10], dist[NMAX], v[2 * UMAX + 10], where[NMAX];
bool vis[NMAX];
vector<Edge *> FN[2 * UMAX + 10];
vector<int> G[NMAX];

void BFS(int S) {
    memset(vis, 0, sizeof vis);

    queue<int> Q;
    Q.push(S);
    vis[S] = 1;
    dist[S] = 0;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        for (const int &it: G[now]) {
            if (vis[it])
                continue;
            vis[it] = 1;
            dist[it] = dist[now] + 1;
            Q.push(it);
        }
    }
}

void AddEdge(int from, int to, int cap, int cost) {
    Edge *dir = new Edge(from, to, cap, cost);
    Edge *rev = new Edge(to, from, 0, -cost);

    dir->rev = rev;
    rev->rev = dir;

    FN[from].push_back(dir);
    FN[to].push_back(rev);
}

bool inq[2 * UMAX + 10];
Edge *father[2 * UMAX + 10];
bool BellmanFord(int S, int D) {
    memset(dist, inf, sizeof dist);
    dist[S] = 0;

    queue<int> Q;
    Q.push(S);
    inq[S] = 1;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        inq[now] = 0;

        for (const auto &it: FN[now]) {
            if (it->cap == it->flow)
                continue;
            if (dist[it->to] > dist[it->from] + it->cost) {
                dist[it->to] = dist[it->from] + it->cost;
                father[it->to] = it;

                if (inq[it->to] == 0) {
                    Q.push(it->to);
                    inq[it->to] = 1;
                }
            }
        }
    }

    return dist[D] != inf;
}

int MaxFlowMinCost(int S, int D) {
    int answer = 0;
    while (BellmanFord(S, D)) {
        int add = inf;

        Edge *now = father[D];
        while (now) {
            add = min(add, now->cap - now->flow);
            now = father[now->from];
        }

        now = father[D];
        while (now) {
            now->flow += add;
            now->rev->flow -= add;
            now = father[now->from];
        }

        answer += add * dist[D];
    }

    return answer;
}

int main() {
    assert(freopen("atac2.in", "r", stdin));
    assert(freopen("atac2.out", "w", stdout));

    int i, j;
    int x, y;

    cin >> N >> M >> U >> X;

    for (i = 1; i <= U; ++i)
        cin >> u[i];

    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    int now = UMAX;
    for (const int &it: G[X]) {
        if (where[it])
            continue;
        where[it] = ++now;
    }

    int S = 2 * UMAX + 8, D = 2 * UMAX + 9;

    for (i = 1; i <= U; ++i) {
        AddEdge(S, i, 1, 0);

        BFS(u[i]);
        for (const int &it: G[X])
            AddEdge(i, where[it], 1, dist[it]);
    }

    for (i = UMAX + 1; i <= now; ++i)
        AddEdge(i, D, 1, 0);

    cout << MaxFlowMinCost(S, D) << '\n';

    return 0;
}
