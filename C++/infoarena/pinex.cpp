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

const int64 BMAX = 1000000000010LL;
const int SMAX = 500010;

ifstream in("pinex.in");
ofstream out("pinex.out");

int M;
int64 A, B;
bool sieve[SMAX];
vector<int> primes, factorization;

inline void Eratosthenes_Sieve() {
    int i, j;
    primes.push_back(2);
    for(i = 3; 1LL * i * i < BMAX; i += 2) {
        if(sieve[(i - 1) / 2]) continue;
        primes.push_back(i);
        for(j = 3 * i; 1LL * j * j < BMAX; j += 2 * i)
            sieve[(j - 1) / 2] = 1;
    }
}

int main() {
    int i, j, k;
    int64 res, multiplier;

    Eratosthenes_Sieve();

    for(in >> M; M; --M) {
        factorization.clear();
        res = 0;

        in >> A >> B;

        for(i = 0; i < (int)primes.size() && B > 1 && 1LL * primes[i] * primes[i] <= B; ++i) {
            if(B % primes[i]) continue;
            factorization.push_back(primes[i]);
            while(B % primes[i] == 0) B /= primes[i];
        }

        if(B > 1) factorization.push_back(B);

        for(j = 0; j < (1 << factorization.size()); ++j) {
            multiplier = 1;
            int nr = 0, sign;
            for(k = 0; k < (int)factorization.size(); ++k)
                if(j & (1 << k)) {
                    multiplier *= factorization[k];
                    ++nr;
                }

            if (nr % 2) sign = -1;
            else sign = 1;

            res += sign * A / multiplier;
        }

        out << res << '\n';
    }

    in.close(), out.close();
    return 0;
}
