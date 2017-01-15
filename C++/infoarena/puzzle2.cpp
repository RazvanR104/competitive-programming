#include <bits/stdc++.h>

using namespace std;

const int MMAX = 400010, NMAX = 100020;

int N, M, C, R, curr_pos;
int curr[NMAX], next_line[NMAX];
bool locked[NMAX];
vector<int> G[NMAX];

void Print() {
    for (int i = 1; i <= C; ++i) {
        cout << curr[i] << ' ';
        assert(curr[i]);
    }
    cout << '\n';
    memcpy(curr, next_line, sizeof(int) * (C + 10));
    memset(next_line, 0, sizeof(int) * (C + 10));
}

int Neighbour(int node, int seek) {
    for (const int &it: G[node])
        if (it == seek)
            return 1;
    return 0;
}

void DFS(int node, int from) {
    curr[++curr_pos] = node;
    for (const int &it: G[node])
        if (it != from)
            DFS(it, node);
}

int main() {
    assert(freopen("puzzle2.in", "r", stdin));
    assert(freopen("puzzle2.out", "w", stdout));

    int i, j, x, y;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (i = 1; i <= N; ++i) {
        if (G[i].size() == 1) {
            DFS(i, -1);
            cout << "1 " << curr_pos << '\n';
            C = curr_pos;
            Print();
            return 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (G[i].size() == 2) {
            curr[++curr_pos] = i;
            locked[i] = 1;
            break;
        }
    }

    for (const int &it: G[curr[curr_pos]]) {
        if (next_line[curr_pos] == 0) {
            next_line[curr_pos] = it;
            locked[it] = 1;
        } else {
            curr[++curr_pos] = it;
            locked[it] = 1;
        }
    }

    while (G[curr[curr_pos]].size() == 3) {
        for (const int &it: G[curr[curr_pos]]) {
            if (Neighbour(it, next_line[curr_pos - 1]) && locked[it] == 0) {
                next_line[curr_pos] = it;
                locked[it] = 1;
                break;
            }
        }

        for (const int &it: G[curr[curr_pos]]) {
            if (locked[it] == 0) {
                locked[it] = 1;
                curr[++curr_pos] = it;
                break;
            }
        }
    }

    for (const int &it: G[curr[curr_pos]]) {
        if (locked[it] == 0) {
            next_line[curr_pos] = it;
            locked[it] = 1;
            break;
        }
    }

    C = curr_pos, R = 1;
    while (M > (R - 1) * C + (C - 1) * R)
        ++R;

    cout << R << ' ' << C << '\n';
    Print();

    for (i = 2; i < R; ++i) {
        for (j = 1; j <= C; ++j) {
            for (const int &it: G[curr[j]]) {
                if (locked[it] == 0) {
                    locked[it] = 1;
                    next_line[j] = it;
                    break;
                }
            }
        }
        Print();
    }
    if (curr[1])
        Print();

    return 0;
}
