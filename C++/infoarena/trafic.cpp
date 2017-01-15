#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200;
const int inf = 0x3f3f3f3f, inf2 = 6000;

int N, M, K;
int dist1[NMAX], distN[NMAX];
vector<int> G[NMAX], C[NMAX];
vector<tuple<int, int, int> > Edges;

struct FlowEdge {
	int x, y, c, f;
	FlowEdge *rev;

	FlowEdge(int x, int y, int c, int f, FlowEdge *rev):
		x(x),
		y(y),
		c(c),
		f(f),
		rev(rev) {
	}
};
vector<FlowEdge *> FN[NMAX];
FlowEdge *from[NMAX];

void addEdge(int x, int y, int c) {
	FlowEdge *dir = new FlowEdge(x, y, c, 0, 0);
	FlowEdge *rev = new FlowEdge(y, x, c, 0, 0);
	dir->rev = rev;
	rev->rev = dir;
	FN[x].push_back(dir);
	FN[y].push_back(rev);
}

void Dijkstra(int source, int *dist) {
	priority_queue<pair<int, int> > PQ;
	PQ.push({0, source});

	memset(dist, inf, sizeof(int) * (N + 1));
	dist[source] = 0;

	while (!PQ.empty()) {
		pair<int, int> now = PQ.top();
		PQ.pop();
		if (-dist[now.second] != now.first)
			continue;
		for (int it = 0; it < int(G[now.second].size()); ++it) {
			if (dist[G[now.second][it]] > dist[now.second] + C[now.second][it]) {
				dist[G[now.second][it]] = dist[now.second] + C[now.second][it];
				PQ.push({-dist[G[now.second][it]], G[now.second][it]});
			}
		}
	}
}

bool BFS(int S, int D) {
	memset(from, 0, sizeof from);
	queue<int> Q;
	Q.push(S);

	from[S] = (FlowEdge *)-1;
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (int i = 0; i < int(FN[now].size()); ++i) {
			FlowEdge *it = FN[now][i];
			if (from[it->y] || it->f >= it->c)
				continue;
			from[it->y] = it;
			Q.push(it->y);
		}
	}
	return from[D] != 0;
}

int EdmondsKarp(int S, int D) {
	int flow = 0;
	while (BFS(S, D)) {
		for (int it = 0; it < int(FN[D].size()); ++it) {
			if (from[FN[D][it]->y] == 0)
				continue;
			int augument = inf;
			FlowEdge *temp = FN[D][it]->rev;
			while (from[temp->x] != (FlowEdge *)-1) {
				augument = min(augument, temp->c - temp->f);
				temp = from[temp->x];
			}
			augument = min(augument, temp->c - temp->f);

			temp = FN[D][it]->rev;
			while (from[temp->x] != (FlowEdge *)-1) {
				temp->f += augument;
				temp->rev->f -= augument;
				temp = from[temp->x];
			}
			temp->f += augument;
			temp->rev->f -= augument;

			flow += augument;
		}
	}
	return flow;
}

bool Check(int value) {
	//for (int i = 1; i <= N; ++i) {
	//  for (int j = 0; j < int(G[i].size()); ++j) {
	for (const auto &it: Edges) {
		int from, to, cost;
		tie(from, to, cost) = it;
		int x = dist1[from];
		int y = cost;
		int z = distN[to];
		int left = value - x;
		int right = value - z;
		if (left > 0 && right > 0 && left + right >= y) {
			addEdge(from, to, 1);
			continue;
		}
		x = distN[from];
		z = dist1[to];
		left = value - x;
		right = value - z;
		if (left > 0 && right > 0 && left + right >= y) {
			addEdge(from, to, 1);
			continue;
		}
		x = dist1[from];
		z = distN[from];
		left = value - x;
		right = value - z;
		if (left > 0 && right > 0) {
			addEdge(from, to, 1);
			continue;
		}
		x = dist1[to];
		z = distN[to];
		left = value - x;
		right = value - z;
		if (left > 0 && right > 0) {
			addEdge(from, to, 1);
			continue;
		}
		addEdge(from, to, inf2);
	}

	bool answer = EdmondsKarp(1, N) <= K;

	for (int i = 1; i <= N; ++i) {
//      for (int j = 0; j < int(FN[i].size()); ++j)
//          delete FN[i][j];
		FN[i].clear();
	}

	return answer;
}

int main() {
	assert(freopen("trafic.in", "r", stdin));
	assert(freopen("trafic.out", "w", stdout));

	int i;

	cin >> N >> M >> K;
	for (i = 1; i <= M; ++i) {
		int x, y, c;
		cin >> x >> y >> c;
		c *= 1000;
		G[x].push_back(y);
		G[y].push_back(x);
		C[x].push_back(c);
		C[y].push_back(c);
		Edges.push_back(make_tuple(x, y, c));
	}

	Dijkstra(1, dist1);
	Dijkstra(N, distN);

	int answer = 0;
	for (int bit = (1 << 30); bit; bit >>= 1)
		if (!Check(answer + bit))
			answer += bit;
	++answer;

	if (Check(answer))
		cout << fixed << setprecision(1) << answer / 1000.0 << '\n';
	else
		cout << "-1\n";

	return 0;
}
