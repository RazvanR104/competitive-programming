#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long int64;

const int NMAX = 25010, LMAX = 110;

ifstream in("dictree.in");
ofstream out("dictree.out");

int N;
int sword[NMAX];
char word[NMAX][LMAX];

struct compare {
    bool operator()(const int &lhs, const int &rhs) const {
        int i;
        for (i = 0; word[lhs][i] && word[rhs][i]; ++i) {
            if (word[lhs][i] < word[rhs][i]) return true;
            if (word[lhs][i] > word[rhs][i]) return false;
        }

        if (word[lhs][i] == 0 && word[rhs][i]) return true;
        if (word[lhs][i] && word[rhs][i] == 0) return false;

        return false;
    }
};

int main() {
    int i, j, res = 1;

    in >> N;
    in.getline(word[1], LMAX);

    for (i = 1; i <= N; ++i) {
        in.getline(word[i], LMAX);
        sword[i] = i;
    }

    sort(sword + 1, sword + N + 1, compare());

    for (i = 1; i <= N; ++i) {
        bool pre = false;
        for (j = 0; word[sword[i]][j]; ++j) {
            if (word[sword[i - 1]][j] == 0 || word[sword[i - 1]][j] != word[sword[i]][j]) pre = true;
            if ((pre == false && word[sword[i - 1]][j] != word[sword[i]][j]) || pre) ++res;
        }
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
