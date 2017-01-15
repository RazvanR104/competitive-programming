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

ifstream in("cumpanit.in");
ofstream out("cumpanit.out");

const int primes[] = { 0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 }, FMAX = 16;

int64 A, B;
int F[FMAX], last[FMAX];
bool used[FMAX];
vector<int64> res;

void Compute_2(int level, int sum, const int64 &current) {
    int64 new_prod = current;

    if (level == 0) {
        if (current >= A) res.push_back(current);
        return;
    }

    if (level == 1) {
        if (sum == 0) return;

        for (int i = 1; i <= sum; ++i) {
            new_prod *= F[level];
            if (new_prod > B) return;
        }

        return Compute_2(level - 1, 0, new_prod);
    }

    for (int i = 1; i <= sum; ++i) {
        new_prod *= F[level];
        if (new_prod > B) break;
        Compute_2(level - 1, sum - i, new_prod);
    }
}

void Compute() {
    int sum = 0, i;
    for (i = 1; F[i]; ++i)
        sum += F[i];

    Compute_2(i - 1, sum, 1);
}

void Comb(int level, const int64 &current, int sum) {
    if (level == 0)
        return Compute();

    int64 new_prod;
    for (int i = last[level + 1] + 1; i < 16; ++i) {
        if (used[i]) continue;
        if (sum + primes[i] > 50) return;
        used[i] = true;
        new_prod = current * primes[i];
        if (new_prod > B) {
            used[i] = false;
            return;
        }
        F[level] = primes[i];
        last[level] = i;
        Comb(level - 1, new_prod, sum + primes[i]);
        used[i] = false;
    }
}

int main() {
    in >> A >> B;

    for (int i = 1; i <= 5; ++i) Comb(i, 1, 0);

    sort(res.begin(), res.end());
    for (int i = 0; i < (int)res.size(); ++i)
        out << res[i] << '\n';

    in.close(), out.close();
    return 0;
}
