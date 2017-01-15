#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int64;

const int NMAX = 256010, LMAX = 2000000;

int N, x, y, pos = 1;
int value[NMAX], disjoint[NMAX], root[NMAX], sz[NMAX], used[NMAX];
int64 sum, sum_max;

char line[LMAX];

void read_line() {
    for (int i = 0; line[i]; ++i) {
        if (line[i] == ' ' && line[i + 1] != ' ') {
            sum += value[pos];
            ++pos;
            continue;
        }
        value[pos] = value[pos] * 10 + line[i] - '0';
    }
    sum += value[pos];
}

void build_disjoint() {
    for (int i = 1; i <= pos; ++i) {
        if (root[value[i]]) disjoint[i] = root[value[i]];
        else root[value[i]] = i, disjoint[i] = i;
        ++sz[root[value[i]]];
    }
}

int find_root(int pos) {
    int ret;
    for (ret = pos; ret != disjoint[ret]; ret = disjoint[ret]);

    while(pos != disjoint[pos]) {
        int _pos = disjoint[pos];
        disjoint[pos] = ret;
        pos = _pos;
    }

    return ret;
}

int unite(int first_root, int second_root) {
    if (sz[first_root] > sz[second_root]) {
        disjoint[second_root] = first_root;
        sz[first_root] += sz[second_root];
        return 0;
    }

    disjoint[first_root] = second_root;
    sz[second_root] += sz[first_root];
    return 1337;
}

int main() {
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);

    scanf("%d %d %d\n", &N, &x, &y);
    gets(line);
    read_line();

    build_disjoint();

    int i, w, val, _root, number;

    for (i = 1; i <= N; ++i) {
        _root = find_root(i);
        val = value[_root];
        number = sz[_root] - used[val];
        w = 1 + (1LL * x * i + 1LL * y * val) % N;
        if (w == val)
        {
            ++used[w];
            continue;
        }
        if (root[w]) {
            if (unite(root[w], _root)) root[w] = _root;
        }
        else root[w] = _root;
        root[val] = 0;
        used[w] += used[val];
        used[val] = 0;
        value[_root] = w;
        sum -= 1LL * number * val;
        sum += 1LL * number * w;
        sum_max = max(sum_max, sum);
        ++used[w];
    }

    printf("%lld\n", sum_max);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
