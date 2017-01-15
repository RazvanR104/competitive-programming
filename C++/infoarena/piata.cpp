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

ifstream in("piata.in");
ofstream out("piata.out");

const int NMAX = 40010;

int N;
int Sum[NMAX];

int main() {
    int i, iT, jT, iM, jM, res = 0;

    in >> N >> iT >> jT >> iM >> jM;
    for(i = 1; i <= N; ++i) {
        int ci = i, sum = 0;
        while(ci) {
            sum += ci % 10;
            ci /= 10;
        }
        Sum[i] = Sum[i - 1] + sum;
    }

    for(i = iT; i <= iM; ++i) {
        int posT, posM;
        posT = jT - i + 1;
        if (posT < 1) posT += N;

        posM = jM - i + 1;
        if (posM < 1) posM += N;

        if (posT <= posM) res += Sum[posM] - Sum[posT - 1];
        else res += Sum[N] - Sum[posT - 1] + Sum[posM];
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
