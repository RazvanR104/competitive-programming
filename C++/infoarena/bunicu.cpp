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

typedef unsigned int uint;

ifstream in("bunicu.in");
ofstream out("bunicu.out");

const int NMAX = 1010, MULT1 = 2, MULT2 = 3;

int T, N;
char str[NMAX], res[NMAX];
pair<uint, uint> hashes[NMAX];

bool exists(uint hash1, uint hash2) {
    int mid, left = 1, right = N;
    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
        if (hashes[mid].first == hash1) {
            if (hashes[mid].second == hash2) return true;
            if (hashes[mid].second > hash2) right = mid - 1;
            else left = mid + 1;
        }
        else if (hashes[mid].first > hash1) right = mid - 1;
        else left = mid + 1;
    }

    return false;
}

int main() {
    int i, j;

    for (in >> T; T; --T) {
        srand(time(NULL));
        in >> N;
        in.getline(str + 1, NMAX);
        for (i = 1; i <= N; ++i) {
            hashes[i].first = hashes[i].second = 0;
            in.getline(str + 1, NMAX);
            for (j = 1; str[j]; ++j) {
                hashes[i].first = hashes[i].first * MULT1 + str[j] - '0';
                hashes[i].second = hashes[i].second * MULT2 + str[j] - '0';
            }
        }
        sort(hashes + 1, hashes + N + 1);

        bool ok = false;
        do {
            uint hash1 = 0, hash2 = 0;
            for (i = 1; i <= N; ++i) {
                res[i] = rand() % 2;
                hash1 = hash1 * MULT1 + res[i];
                hash2 = hash2 * MULT2 + res[i];
                res[i] += '0';
            }

            if (exists(hash1, hash2)) ok = true;
            else ok = false;
        } while(ok);

        res[N + 1] = 0;
        out << res + 1 << '\n';
    }

    in.close(), out.close();
    return 0;
}
