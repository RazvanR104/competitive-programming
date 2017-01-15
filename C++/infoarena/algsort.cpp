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

ifstream in("algsort.in");
ofstream out("algsort.out");

const int NMAX = 500010;

int N;
int V[NMAX];

int Partition(int left, int right) {
    int pivot_index = left + rand() % (right - left + 1), pos = left;
    swap(V[pivot_index], V[right]);

    for (int i = left; i < right; ++i)
        if (V[i] < V[right])
            swap(V[i], V[pos++]);

    swap(V[right], V[pos]);
    return pos;
}

void QuickSort(int left, int right) {
    if (left >= right) return;

    int Part = Partition(left, right);
    QuickSort(left, Part);
    QuickSort(Part + 1, right);
}

int main() {
    int i;
    srand(time(NULL));

    in >> N;
    for (i = 1; i <= N; ++i) in >> V[i];

    QuickSort(1, N);
    for (i = 1; i <= N; ++i) out << V[i] << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
