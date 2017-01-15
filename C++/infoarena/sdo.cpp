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

ifstream in("sdo.in");
ofstream out("sdo.out");

const int NMAX = 3000010;

int N, K;
int V[NMAX];

int Partition(int left, int right) {
    int pivot_index = left + rand() % (right - left + 1), i, pos = left;
    swap(V[right], V[pivot_index]);

    for (i = left; i < right; ++i)
        if (V[i] < V[right])
            swap(V[i], V[pos++]);
    swap(V[right], V[pos]);
    return pos;
}

void Select(int left, int right, int pos) {
    if (left >= right) return;

    int Part = Partition(left, right);
    int num = Part - left + 1;

    if (pos <= num) Select(left, Part, pos);
    else Select(Part + 1, right, pos - num);
}

int main() {
    srand(time(NULL));
    int i;

    in >> N >> K;
    for (i = 1; i <= N; ++i)
        in >> V[i];

    Select(1, N, K);
    out << V[K] << '\n';

    in.close(), out.close();
    return 0;
}
