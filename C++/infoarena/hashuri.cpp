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

ifstream in("hashuri.in");
ofstream out("hashuri.out");

const int MOD = 666013;

int N, M;
vector<int> L[MOD];

void hash_insert(const int &value) {
    int pos = value % MOD;
    if (find(L[pos].begin(), L[pos].end(), value) == L[pos].end()) L[pos].push_back(value);
}

void hash_erase(const int &value) {
    int pos = value % MOD;
    vector<int>::iterator it = find(L[pos].begin(), L[pos].end(), value);

    if (it == L[pos].end()) return;
    L[pos].erase(it);
}

bool hash_exists(const int &value) {
    int pos = value % MOD;
    return (find(L[pos].begin(), L[pos].end(), value) != L[pos].end());
}

int main() {
    int op, value;

    for (in >> N; N; --N) {
        in >> op >> value;

        if (op == 1) hash_insert(value);
        else if (op == 2) hash_erase(value);
        else out << ((hash_exists(value)) ? (1) : (0)) << '\n';
    }

    in.close(), out.close();
    return 0;
}
