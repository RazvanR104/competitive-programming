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

ifstream in("cutie.in");
ofstream out("cutie.out");

const int NMAX = 10010;

int T, N, M, K;
int Leak[NMAX];
vector<pair<int, int> > B;

int GetPosition(int value) {
    int left = 1, right = K, mid, ret = 0;

    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
        if (value == Leak[mid]) return mid;
        else if (value > Leak[mid]) {
            ret = mid;
            left = mid + 1;
        } else right = mid - 1;
    }

    return ret;
}

int main() {
    int i, b;

    for (in >> T; T; --T) {
        in >> N >> K >> M;

        for (i = 1; i <= K; ++i) in >> Leak[i];

        B.clear();
        for (i = 1; i <= M; ++i) {
            in >> b;
            if (B.size() == 0 || B[B.size() - 1].first != b) B.push_back(make_pair(b, 1));
            else ++B[B.size() - 1].second;
        }

        Leak[0] = 1;
        Leak[K + 1] = N;

        int num1 = 0, num2 = 0, num3 = 0;
        for (i = 0; i < (int)B.size(); ++i) {
            int pos = GetPosition(B[i].first);

            int left = 0, right = 0;
            left = B[i].first - Leak[pos];
            right = Leak[pos + 1] - B[i].first;
            if (left % 2 == 1 && right % 2 == 1) num3 += B[i].second;
            else if (left % 2 == 1 || right % 2 == 1) num2 += B[i].second;
            else num1 += B[i].second;
        }

        if (num3 % 2 == 1) out << '1';
        else if (num3 % 2 == 0 && num2 % 2 == 1) out << '1';
        else out << '0';
    }

    out << '\n';
    in.close(), out.close();
    return 0;
}
