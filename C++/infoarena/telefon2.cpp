#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int N, curr;
int G[NMAX], where[NMAX];
vector<int> GT[NMAX], path[NMAX];
bool instack[NMAX], vis[NMAX], incycle[NMAX];

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

void DFS(int node) {
	vis[node] = 1;
	if (GT[node].size() == 0) {
		path[curr].push_back(node);
		where[node] = curr++;
		return;
	}
	int Max = -1, _where;
	for (const int &it: GT[node]) {
		if (vis[it] || incycle[it])
			continue;
		DFS(it);
		if (Max < int(path[where[it]].size())) {
			Max = path[where[it]].size();
			_where = where[it];
		}
	}

	if (Max != -1) {
		path[_where].push_back(node);
		where[node] = _where;
	} else {
		path[curr].push_back(node);
		where[node] = curr++;
	}
}

int main() {
	assert(freopen("telefon2.in", "r", stdin));
	assert(freopen("telefon2.out", "w", stdout));

	Reader cin("telefon2.in");

	int i, j;
	cin >> N;
	for (i = 1; i <= N; ++i) {
		cin >> j;
		G[i] = j;
		GT[j].push_back(i);
	}

	stack<int> S;
	vector<int> cycle;
	for (i = 1; i <= N; ++i) {
		if (vis[i])
			continue;
		S.push(i);
		instack[i] = 1;
		while (instack[G[S.top()]] == 0) {
			S.push(G[S.top()]);
			instack[S.top()] = 1;
		}
		int until = G[S.top()];
		cycle.push_back(until);
		incycle[until] = 1;
		while (S.top() != until) {
			cycle.push_back(S.top());
			instack[S.top()] = 0;
			incycle[S.top()] = 1;
			S.pop();
		}
		while (!S.empty()) {
			instack[S.top()] = 0;
			S.pop();
		}

		int Max = -1, _where;
		for (j = 0; j < int(cycle.size()); ++j) {
			DFS(cycle[j]);
			if (Max < (int)path[where[cycle[j]]].size()) {
				Max = path[where[cycle[j]]].size();
				_where = j;
			}
		}

		int _path = where[cycle[_where]];
		for (j = _where - 1; j >= 0; --j) {
			path[_path].push_back(cycle[j]);
			path[where[cycle[j]]].pop_back();
			where[cycle[j]] = _path;
		}
		for (j = int(cycle.size()) - 1; j > _where; --j) {
			path[_path].push_back(cycle[j]);
			path[where[cycle[j]]].pop_back();
			where[cycle[j]] = _path;
		}

		cycle.clear();
	}

	int ans = 0;
	for (i = 0; i < curr; ++i)
		ans += path[i].size() > 0;

	/*for (i = 0; i < curr; ++i) {
		for (const int &it: path[i])
			cout << it << ' ';
		cout << '\n';
	}*/

	printf("%d\n", ans == 1 ? 0 : ans);
	if (ans == 1)
		return 0;

	int top = -1, bottom = -1;
	for (i = 0; i < curr; ++i) {
		if (path[i].size() == 0)
			continue;
		if (top == -1) {
			top = path[i].front();
			bottom = path[i].back();
		} else {
			printf("%d %d\n", bottom, path[i].front());
			//cout << bottom << ' ' << path[i].front() << '\n';
			bottom = path[i].back();
		}
	}
	printf("%d %d\n", bottom, top);

	return 0;
}
