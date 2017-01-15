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

ifstream in("semipal.in");
ofstream out("semipal.out");

int T, N;
int64 K;

int main() {
    int i;
    char first_and_last;
    int64 pos;

    for (in >> T; T; --T) {
        in >> N >> K;
        pos = 1LL << (N - 2);
        if (K > pos) {
            first_and_last = 'b';
            K -= pos;
        }
        else first_and_last = 'a';

        --K;
        out << first_and_last;
        for (i = N - 3; i >= 0; --i)
            if ((K >> i) & 1) out << 'b';
            else out << 'a';
        out << first_and_last << '\n';
    }

    in.close(), out.close();
    return 0;
}
