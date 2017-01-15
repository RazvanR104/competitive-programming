#include <bits/stdc++.h>

using namespace std;

const int NMAX = 40010, inf = 0x3f3f3f3f, KMAX = 210;

int N, M, K;
//vector<int> G[NMAX], neigh[NMAX];
int G[NMAX][3], neigh[NMAX][3];
pair<int, int> prv[NMAX][3];
//vector<pair<int, int>> prv[NMAX];

const int BUFFER_SIZE = 1 << 20;
class InputReader {
    public:
        InputReader() {}
        InputReader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline InputReader & operator >> (int &n) {
            n = 0;
            sign = 1;
            while(!isdigit(buffer[cursor])) {
                if (buffer[cursor] == '-') sign = -1;
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            n *= sign;
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

void ComputeNeighbours(int x, int y) {
    int node = x, i, last = y;
    int kx[2 * KMAX];

    int left = KMAX, right = KMAX;
    bool ok = 1;
    for (i = 1; i <= K && ok; ++i)  {
        kx[--left] = node;
        ok = 0;
        for (int j = 1; j <= G[node][0]; ++j)
            if (G[node][j] != last) {
                last = node;
                node = G[node][j];
                ok = 1;
                break;
            }
    }

    ok = 1;
    node = y, last = x;
    for (i = 1; i <= K && ok; ++i)  {
        kx[right++] = node;
        ok = 0;
        for (int j = 1; j <= G[node][0]; ++j)
            if (G[node][j] != last) {
                last = node;
                node = G[node][j];
                ok = 1;
                break;
            }
    }

    for (i = left; i + K < right; ++i) {
        neigh[kx[i]][++neigh[kx[i]][0]] = kx[i + K];
        prv[kx[i]][neigh[kx[i]][0]] = {kx[i + 1], kx[i + K - 1]};
        neigh[kx[i + K]][++neigh[kx[i + K]][0]] = kx[i];
        prv[kx[i + K]][neigh[kx[i + K]][0]] = {kx[i + K - 1], kx[i + 1]};
    }
}

bool Find(int pos, int value) {
    for (int i = 1; i <= G[pos][0]; ++i)
        if (G[pos][i] == value)
            return 1;
    return 0;
}

void EraseNeigh(int pos, int value) {
    if (neigh[pos][0] == 0)
        return;
    if (neigh[pos][1] == value) {
        if (neigh[pos][0] >= 2) {
            neigh[pos][1] = neigh[pos][2];
            prv[pos][1] = prv[pos][2];
        }
        --neigh[pos][0];
        return;
    }
    if (neigh[pos][0] == 1)
        return;
    if (neigh[pos][2] == value) {
        --neigh[pos][0];
        return;
    }
}

void DeleteNeighbours(int x, int y) {
    int node = x, i, last = y;
    int kx[2 * KMAX];

    int left = KMAX, right = KMAX;
    bool ok = 1;
    for (i = 1; i <= K && ok; ++i)  {
        kx[--left] = node;
        ok = 0;
        for (int j = 1; j <= G[node][0]; ++j)
            if (G[node][j] != last) {
                last = node;
                node = G[node][j];
                ok = 1;
                break;
            }
    }

    ok = 1;
    node = y, last = x;
    for (i = 1; i <= K && ok; ++i)  {
        kx[right++] = node;
        ok = 0;
        for (int j = 1; j <= G[node][0]; ++j)
            if (G[node][j] != last) {
                last = node;
                node = G[node][j];
                ok = 1;
                break;
            }
    }

    for (i = left; i + K < right; ++i) {
        EraseNeigh(kx[i], kx[i + K]);
        EraseNeigh(kx[i + K], kx[i]);
    }
}

pair<int, int> ChainEndNodes(int x) {
    if (G[x][0] == 0)
        return {x, x};

    int st = x, last = x;
    int last_nd = x, last_2 = x;
    bool jumped = 0, ok;

    if (neigh[st][0]) {
        last_nd = prv[st][1].first;
        last_2 = prv[st][1].second;
        st = neigh[st][1];
        jumped = 1;

        do {
            ok = 0;
            //for (const int &it : neigh[st]) {
            for (int i = 1; i <= neigh[st][0]; ++i) {
                if (neigh[st][i] != last) {
                    last_2 = prv[st][i].second;
                    last = st;
                    st = neigh[st][i];
                    ok = 1;
                    break;
                }
            }
        } while (ok);
    }

    bool cont = 0;
    for (int i = 1; i <= G[st][0]; ++i) {
        if (G[st][i] != last_2) {
            last = st;
            st = G[st][i];
            cont = 1;
            break;
        }
    }

    if (jumped == 0) {
        last_nd = st;
    }

    if (cont) {
        do {
            ok = 0;
            for (int i = 1; i <= G[st][0]; ++i) {
                if (G[st][i] != last) {
                    last = st;
                    st = G[st][i];
                    ok = 1;
                    break;
                }
            }
        } while (ok);
    }

    jumped = 0;
    int nd = x;
    if (neigh[nd][0] > 1) {
        last = nd;
        last_2 = prv[nd][2].second;
        nd = neigh[nd][2];
        jumped = 1;

        do {
            ok = 0;
            //for (const int &it : neigh[nd]) {
            for (int i = 1; i <= neigh[nd][0]; ++i) {
                if (neigh[nd][i] != last) {
                    last_2 = prv[nd][i].second;
                    last = nd;
                    nd = neigh[nd][i];
                    ok = 1;
                    break;
                }
            }
        } while (ok);
    }

    if (jumped == 0) {
        ok = 0;
        for (int i = 1; i <= G[nd][0]; ++i) {
            if (G[nd][i] != last_nd) {
                last = nd;
                nd = G[nd][i];
                ok = 1;
                break;
            }
        }
    } else {
        ok = 0;
        for (int i = 1; i <= G[nd][0]; ++i) {
            if (G[nd][i] != last_2) {
                last = nd;
                nd = G[nd][i];
                ok = 1;
                break;
            }
        }
    }

    if (ok) {
        do {
            ok = 0;
            for (int i = 1; i <= G[nd][0]; ++i) {
                if (G[nd][i] != last) {
                    last = nd;
                    nd = G[nd][i];
                    ok = 1;
                    break;
                }
            }
        } while (ok);
    }

    if (st <= nd)
        return {st, nd};
    return {nd, st};
}

pair<int, int> DistanceDNodes(int x, int D) {
    int st = x, last = x;
    int last_nd = x, last_2 = x;
    bool jumped = 0, ok;

    int _D = D;

    if (neigh[st][0] && _D >= K) {
        last_nd = prv[st][1].first;
        last_2 = prv[st][1].second;
        st = neigh[st][1];
        jumped = 1;
        _D -= K;

        if (_D >= K) {
        do {
            ok = 0;
            //for (const int &it : neigh[st]) {
            for (int i = 1; i <= neigh[st][0]; ++i) {
                if (neigh[st][i] != last) {
                    last_2 = prv[st][i].second;
                    last = st;
                    st = neigh[st][i];
                    ok = 1;
                    _D -= K;
                    break;
                }
            }
        } while (ok && _D >= K);
        }
    }

    bool cont = 0;
    if (_D) {
    for (int i = 1; i <= G[st][0]; ++i) {
        if (G[st][i] != last_2) {
            last = st;
            st = G[st][i];
            cont = 1;
            --_D;
            break;
        }
    }
    }

    if (jumped == 0) {
        last_nd = st;
    }

    if (cont && _D) {
        do {
            ok = 0;
            for (int i = 1; i <= G[st][0]; ++i) {
                if (G[st][i] != last) {
                    last = st;
                    st = G[st][i];
                    ok = 1;
                    --_D;
                    break;
                }
            }
        } while (ok && _D);
    }

    if (_D)
        st = inf;

    _D = D;

    jumped = 0;
    int nd = x;
    if (neigh[nd][0] > 1 && _D >= K) {
        last = nd;
        last_2 = prv[nd][2].second;
        nd = neigh[nd][2];
        jumped = 1;
        _D -= K;

        if (_D >= K) {
        do {
            ok = 0;
            //for (const int &it : neigh[nd]) {
            for (int i = 1; i <= neigh[nd][0]; ++i) {
                if (neigh[nd][i] != last) {
                    last_2 = prv[nd][i].second;
                    last = nd;
                    nd = neigh[nd][i];
                    ok = 1;
                    _D -= K;
                    break;
                }
            }
        } while (ok && _D >= K);
        }
    }

    if (jumped == 0 && _D) {
        ok = 0;
        for (int i = 1; i <= G[nd][0]; ++i) {
            if (G[nd][i] != last_nd) {
                last = nd;
                nd = G[nd][i];
                ok = 1;
                --_D;
                break;
            }
        }
    } else if (_D) {
        ok = 0;
        for (int i = 1; i <= G[nd][0]; ++i) {
            if (G[nd][i] != last_2) {
                last = nd;
                nd = G[nd][i];
                ok = 1;
                --_D;
                break;
            }
        }
    }

    if (ok && _D) {
        do {
            ok = 0;
            for (int i = 1; i <= G[nd][0]; ++i) {
                if (G[nd][i] != last) {
                    last = nd;
                    nd = G[nd][i];
                    ok = 1;
                    --_D;
                    break;
                }
            }
        } while (ok && _D);
    }

    if (_D)
        nd = inf;

    if (st <= nd)
        return {st, nd};
    return {nd, st};
}

void EraseGraph(int pos, int node) {
    if (G[pos][0] == 0)
        return;
    if (G[pos][1] == node) {
        if (G[pos][0] >= 2)
            swap(G[pos][1], G[pos][2]);
        --G[pos][0];
        return;
    }
    if (G[pos][0] == 1)
        return;
    if (G[pos][2] == node)
        --G[pos][0];
}

int main() {
	//ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	//assert(freopen("drumuri4.in", "r", stdin) != NULL);
    //assert(freopen("drumuri4.out", "w", stdout) != NULL);
    #endif

    InputReader fin("drumuri4.in");
    ofstream fout("drumuri4.out");
    //fout.sync_with_stdio(false);

    //scanf("%d %d", &N, &M);
    fin >> N >> M;
    K = 60;

    int op, x, y, D;

    while (M--) {
        //scanf("%d", &op);
        fin >> op;
        if (op == 1) {
            //scanf("%d %d", &x, &y);
            fin >> x >> y;
            if (x > y) swap(x, y);

            if (G[x][0] <= 1 && G[y][0] <= 1) {

                if (G[x][0] == 1 && G[y][0] == 1) {
                    int st, nd;
                    tie(st, nd) = ChainEndNodes(x);
                    if (st == x && nd == y) {
                        fout << "0\n";
                        continue;
                    }
                }

                G[x][++G[x][0]] = y;
                G[y][++G[y][0]] = x;
                ComputeNeighbours(x, y);
                fout << "1\n";
                //printf("1\n");
            } else
                fout << "0\n";
        } else if (op == 2) {
//            scanf("%d %d", &x, &y);
            fin >> x >> y;

            if (!Find(x, y)) {
                fout << "0\n";
                continue;
            }

            fout << "1\n";

            EraseGraph(x, y);
            EraseGraph(y, x);

            DeleteNeighbours(x, y);
        } else if (op == 3) {
         //   scanf("%d %d", &x, &D);
            fin >> x >> D;
            int res1, res2;
            tie(res1, res2) = DistanceDNodes(x, D);

            if (res1 == inf && res2 == inf)
                fout << "0\n";
            else if (res1 == res2)
                fout << "1 " << res1 << '\n';
            else if (res2 == inf)
                fout << "1 " << res1 << '\n';
            else
                fout << "2 " << res1 << ' ' << res2 << '\n';
        } else {
            //scanf("%d", &x);
            fin >> x;
            if (G[x][0] == 0) {
                fout << "1 " << x << '\n';
                continue;
            }

            int res1, res2;
            tie(res1, res2) = ChainEndNodes(x);
            fout << "2 " << res1 << ' ' << res2 << '\n';
        }
    }

	return 0;
}
