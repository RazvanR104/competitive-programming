#include <bits/stdc++.h>

using namespace std;

const int NMAX = 400, inf = 0x3f3f3f3f;

struct Edge {
    int from, to, cap, cost, flow;
    Edge *rev;

    Edge(int from, int to, int cap, int cost) :
        from(from),
        to(to),
        cap(cap),
        cost(cost),
        flow(0),
        rev(0) {
    }
};

int N, M, S, D;
vector<Edge *> G[NMAX];

void AddEdge(int from, int to, int cap, int cost) {
    Edge *dir = new Edge(from, to, cap, cost);
    Edge *rev = new Edge(to, from, 0, -cost);

    dir->rev = rev;
    rev->rev = dir;

    G[from].push_back(dir);
    G[to].push_back(rev);
}

int dist[NMAX];
bool inq[NMAX];
void BellmanFord(int S) {
    memset(dist, inf, sizeof dist);
    dist[S] = 0;

    queue<int> Q;
    Q.push(S);
    inq[S] = 1;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        inq[now] = 0;

        for (const auto &it: G[now]) {
            if (it->cap == 0)
                continue;

            if (dist[it->to] > dist[it->from] + it->cost) {
                dist[it->to] = dist[it->from] + it->cost;

                if (inq[it->to] == 0) {
                    Q.push(it->to);
                    inq[it->to] = 1;
                }
            }
        }
    }
}

int dist2[NMAX], rdist[NMAX];
Edge *father[NMAX];
bool Dijkstra(int S, int D) {
    memset(dist2, inf, sizeof dist2);
    dist2[S] = 0;

    priority_queue<pair<int, int>> PQ;
    PQ.push({0, S});

    while (!PQ.empty()) {
        int cost, node;
        tie(cost, node) = PQ.top();
        PQ.pop();

        if (dist2[node] != -cost)
            continue;

        for (const auto &it: G[node]) {
            if (it->cap - it->flow == 0)
                continue;

            if (dist2[it->to] > dist2[it->from] + it->cost + dist[it->from] - dist[it->to]) {
                dist2[it->to] = dist2[it->from] + it->cost + dist[it->from] - dist[it->to];
                rdist[it->to] = rdist[it->from] + it->cost;

                father[it->to] = it;

                PQ.push({-dist2[it->to], it->to});
            }
        }
    }

    memcpy(dist, rdist, sizeof dist);
    return dist2[D] != inf;
}

int MaxFlowMinCost(int S, int D) {
    int answer = 0;
    BellmanFord(S);
    while (Dijkstra(S, D)) {
        int add = inf;

        Edge *curr = father[D];
        while (curr != 0) {
            add = min(add, curr->cap - curr->flow);
            curr = father[curr->from];
        }

        curr = father[D];
        while (curr != 0) {
            curr->flow += add;
            curr->rev->flow -= add;
            curr = father[curr->from];
        }

        answer += rdist[D] * add;
    }

    return answer;
}

int main() {
    assert(freopen("fmcm.in", "r", stdin));
    assert(freopen("fmcm.out", "w", stdout));

    int i;
    int x, y, c, z;

    scanf("%d %d %d %d", &N, &M, &S, &D);
    for (i = 1; i <= M; ++i) {
        scanf("%d %d %d %d", &x, &y, &c, &z);
        AddEdge(x, y, c, z);
    }

    cout << MaxFlowMinCost(S, D) << '\n';

    return 0;
}
