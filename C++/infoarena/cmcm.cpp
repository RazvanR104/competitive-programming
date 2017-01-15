#include <bits/stdc++.h>

#define eb emplace_back
#define mp make_pair

using namespace std;

const int NMAX = 610, offset = 305, inf = 0x3f3f3f3f;

int N, M, E;
int C[NMAX][NMAX], F[NMAX][NMAX], BF[NMAX], father[NMAX];
bool inqueue[NMAX];

struct Edge {
    int x, y, c;
    Edge() {}
    Edge(int x, int y, int c) {
        this->x = x;
        this->y = y;
        this->c = c;
    }
};

vector<Edge> Edges;
vector<int> Cost[NMAX];
vector<pair<int, int>> G[NMAX];

bool BellmanFord(int S, int D) {
    memset(inqueue, 0, sizeof(inqueue));
    memset(BF, inf, sizeof(BF));

    queue<int> Q;
    Q.push(S);
    inqueue[S] = 1;
    BF[S] = 0;

    while (!Q.empty()) {
        int now = Q.front();
        inqueue[now] = 0;
        Q.pop();

        int j = 0;
        for (const auto &i : G[now]) {
            if (BF[i.first] > BF[now] + Cost[now][j] && F[now][i.first] < C[now][i.first]) {
                BF[i.first] = BF[now] + Cost[now][j];
                father[i.first] = now;
                if (inqueue[i.first] == 0) {
                    Q.push(i.first);
                    inqueue[i.first] = 1;
                }
            }
            ++j;
        }
    }

    return (BF[D] != inf);
}

int main() {
	ios_base::sync_with_stdio(false);
    freopen("cmcm.in", "r", stdin);
    freopen("cmcm.out", "w", stdout);
	freopen("cmcm.err", "w", stderr);

    int i, j, x, y, c;

    cin >> N >> M >> E;

    for (i = 0; i < E; ++i) {
        cin >> x >> y >> c;
        y += offset;
        Edges.eb(x, y, c);
        G[x].eb(mp(y, i));
        G[y].eb(mp(x, i));
        Cost[x].eb(c);
        Cost[y].eb(-c);

        C[x][y] = 1;
    }

    Edges.eb(-1, -1, 0);
    int SD = Edges.size() - 1;

    int S = NMAX - 1, D = NMAX - 2;
    for (i = 1; i <= N; ++i) {
        if (G[i].size() == 0) continue;
        G[S].eb(mp(i, SD));
        Cost[S].eb(0);
        C[S][i] = 1;
    }

    for (i = 1; i <= M; ++i) {
        y = i + offset;
        if (G[y].size() == 0) continue;
        G[y].eb(mp(D, SD));
        Cost[y].eb(0);
        C[y][D] = 1;
    }

    int flow, current, cost = 0;
    vector<int> answer;
    for (flow = 0; BellmanFord(S, D); flow += current) {
        current = inf;
        for (i = D; i != S; i = father[i])
            current = min(current, C[father[i]][i] - F[father[i]][i]);
        for (i = D; i != S; i = father[i]) {
            F[father[i]][i] += current;
            F[i][father[i]] -= current;
        }
    }

    cout << flow << ' ';

    j = 1;
    for (const auto &i : Edges) {
        if (F[i.x][i.y] == 1) {
            answer.eb(j);
            cost += i.c;
        }
        ++j;
    }

    cout << cost << '\n';

    for (const auto &i : answer)
        cout << i << ' ';
    cout << '\n';

	return 0;
}
