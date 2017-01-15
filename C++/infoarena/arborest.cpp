#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010, LG2NMAX = 18;
const int BUFFER_SIZE = 1 << 20;
class Reader {
public:
	Reader() {}
	Reader(const char* filename) {
		file = fopen(filename, "r");
		cursor = 0;
		fread(buffer, BUFFER_SIZE, 1, file);
	}
	inline Reader & operator >> (int &n) {
		n = 0;
		while(!isdigit(buffer[cursor])) {
			advance();
		}
		while(isdigit(buffer[cursor])) {
			n = n * 10 + buffer[cursor] - '0';
			advance();
		}
		return *this;
	}

	inline void close() {
		fclose(file);
	}
private:
	int cursor, sign;
	char buffer[BUFFER_SIZE];
	FILE* file;
	inline void advance() {
		++cursor;
		if(cursor == BUFFER_SIZE) {
			cursor = 0;
			fread(buffer, BUFFER_SIZE, 1, file);
		}
	}
};

int N, K;
int max_height;
vector<int> T[NMAX];
int root[LG2NMAX][NMAX];
pair<int, int> dist[NMAX];
bool vis[NMAX];

void Mark(int node) {
	vis[node] = 1;
	queue<int> Q;
	Q.push(node);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (const int &it: T[now]) {
			if (vis[it])
				continue;
			vis[it] = 1;
			Q.push(it);
		}
	}
}

int Check(int value) {
	int answer = 0;
	for (int i = 1; i <= N && dist[i].first > value; ++i) {
		if (vis[dist[i].second])
			continue;
		int parent = dist[i].second;
		for (int bit = 0; (1 << bit) <= value - 1; ++bit)
			if ((value - 1) & (1 << bit))
				parent = root[bit][parent];
		Mark(parent);
		++answer;
	}
	memset(vis, 0, sizeof vis);
	return answer;
}

int main() {
	Reader cin("arborest.in");
	assert(freopen("arborest.out", "w", stdout));

	int i, j;

	cin >> N >> K;
	for (i = 2; i <= N; ++i) {
		cin >> root[0][i];
		T[root[0][i]].push_back(i);
	}

	queue<int> Q;
	Q.push(1);
	dist[1] = {0, 1};
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (const int &it: T[now]) {
			dist[it] = {dist[now].first + 1, it};
			max_height = max(max_height, dist[it].first);
			Q.push(it);
		}
	}

	for (i = 1; (1 << i) <= N; ++i)
		for (j = 1; j <= N; ++j)
			root[i][j] = root[i - 1][root[i - 1][j]];

	sort(dist + 1, dist + N + 1, greater<pair<int, int>>());

	int answer = 0;
	for (int bit = (1 << LG2NMAX); bit; bit >>= 1)
		if (answer + bit <= max_height && Check(answer + bit) > K)
			answer += bit;

	if (N != 0)
		cout << answer + 1 << '\n';
	else
		cout << "0\n";

	return 0;
}
