#include <fstream>
#include <set>
#include <queue>

using namespace std;

ifstream in("arbciclu.in");
ofstream out("arbciclu.out");

const int NMAX = 100010;

int T, N, M;

set<int> G[NMAX];
queue<int> Q;
char line[100];

void read_line(int &A, int &B) {
    int i = 0;
    in.getline(line, 100);
    A = B = 0;
    for (i = 0; line[i] != ' '; ++i)
        A = A * 10 + line[i] - '0';
    for (++i; line[i]; ++i)
        B = B * 10 + line[i] - '0';
}

int main() {
    int x, y, i;

    for (in >> T, in.get(); T; --T) {
        read_line(N, M);
        for (i = 1; i <= N; ++i) G[i].clear();

        while(M--) {
            read_line(x, y);
            G[x].insert(y);
            G[y].insert(x);
        }

        if (N < 3) {
            out << "NO\n";
            continue;
        }

        for (i = 1; i <= N; ++i)
            if (G[i].size() == 2)
                Q.push(i);

        int node, left, right;

        while(!Q.empty()) {
            node = Q.front();
            Q.pop();
            if (G[node].size() != 2) continue;

            --N;
            set<int>::iterator it = G[node].begin();
            left = *it;
            ++it;
            right = *it;

            G[left].erase(node);
            G[right].erase(node);

            if (G[left].count(right)) {
                if (G[left].size() == 2) Q.push(left);
                if (G[right].size() == 2) Q.push(right);
            }

            G[left].insert(right);
            G[right].insert(left);
        }

        if (N == 2) out << "YES\n";
        else out << "NO\n";
    }

    in.close(), out.close();
    return 0;
}
