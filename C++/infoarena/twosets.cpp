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
typedef unsigned int uint;

const int MOD = 666013, MOD1 = 1000003, MOD2 = 1000039, LMAX = 3145750;

ifstream in("twosets.in");
ofstream out("twosets.out");

int T;
char line[LMAX];
vector<pair<uint, uint> > H[MOD];

bool Check(uint hash_1, uint hash_2) {
    int key = hash_1 % MOD;

    for (int i = 0; i < (int)H[key].size(); ++i)
        if (H[key][i].first == hash_1 && H[key][i].second == hash_2)
            return true;
    return false;
}

void Insert(uint hash_1, uint hash_2) {
    int key = hash_1 % MOD;
    H[key].push_back(make_pair(hash_1, hash_2));
}

int main() {
    int i, excess = 0;
    uint new_hash_1, new_hash_2;
    stack<pair<uint, uint> > S;

    for (in >> T, in.getline(line, LMAX); T; --T) {
        in.getline(line, LMAX);
        S.push(make_pair(0, 0));
        excess = 0;

        for (i = 0; line[i]; ++i) {
            if (line[i] == 'i') {
                new_hash_1 = (S.top().first * 2 + line[i + 1] - '0') % MOD1;
                new_hash_2 = (S.top().second * 2 + line[i + 1] - '0') % MOD2;
                S.push(make_pair(new_hash_1, new_hash_2));
                ++i;
            } else if (line[i] == 't') {
                Insert(S.top().first, S.top().second);
                ++excess;
            } else S.pop();
        }

        in.getline(line, LMAX);

        S = stack<pair<uint, uint> >();
        S.push(make_pair(0, 0));

        for (i = 0; line[i]; ++i) {
            if (line[i] == 'i') {
                new_hash_1 = (S.top().first * 10 + line[i + 1] - '0') % MOD1;
                new_hash_2 = (S.top().second * 10 + line[i + 1] - '0') % MOD2;
                S.push(make_pair(new_hash_1, new_hash_2));
                ++i;
            } else if (line[i] == 't') {
                if (Check(S.top().first, S.top().second)) {
                    --excess;
                } else break;
            } else S.pop();
        }

        if (line[i] || excess != 0) out << "0\n";
        else out << "1\n";

        for (i = 0; i < MOD; ++i) H[i].clear();
        S = stack<pair<uint, uint> >();
    }

    in.close(), out.close();
    return 0;
}
