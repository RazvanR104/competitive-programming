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

ifstream in("base3.in");
ofstream out("base3.out");

const int CMAX = 16010, oo = 0x7fffffff;

int lenA, lenB, lenC;
int state[2 * CMAX];
char A[CMAX], B[CMAX], C[CMAX];
priority_queue<pair <int, int>, vector <pair<int, int> >, greater<pair<int, int> > > Heap;

inline int Abs(const int &value) {
    return (value > 0) ? (value) : (-value);
}

void Concatenate(int cost, int pos, int len) {
    if (pos + len < 2 * CMAX && cost + len < state[pos + len]) {
        state[pos + len] = cost + len;
        Heap.push(make_pair(cost + len, pos + len));
    }
    if (Abs(pos - len) < 2 * CMAX && cost + len < state[Abs(pos - len)]) {
        state[Abs(pos - len)] = cost + len;
        Heap.push(make_pair(cost + len, Abs(pos - len)));
    }
}

int main() {
    int i, cost, state_pos;

    in.getline(A, CMAX);
    in.getline(B, CMAX);
    in.getline(C, CMAX);
    for( ; A[lenA]; ++lenA);
    for( ; B[lenB]; ++lenB);
    for( ; C[lenC]; ++lenC);

    for(i = 0; i < 2 * CMAX; ++i) state[i] = oo;
    for(i = 0; i < lenA; ++i)
        if (A[i] == '1')
            state[Abs(i - (lenA - i - 1))] = min(state[Abs(i - (lenA - i - 1))], lenA);
    for(i = 0; i < lenB; ++i)
        if (B[i] == '1')
            state[Abs(i - (lenB - i - 1))] = min(state[Abs(i - (lenB - i - 1))], lenB);
    for(i = 0; i < lenC; ++i)
        if (C[i] == '1')
            state[Abs(i - (lenC - i - 1))] = min(state[Abs(i - (lenC - i - 1))], lenC);

    for (i = 0; i < 2 * CMAX; ++i)
        if (state[i] != oo)
            Heap.push(make_pair(state[i], i));

    while(!Heap.empty()) {
        cost = Heap.top().first, state_pos = Heap.top().second;
        Heap.pop();

        if (state_pos == 0) break;

        Concatenate(cost, state_pos, lenA);
        Concatenate(cost, state_pos, lenB);
        Concatenate(cost, state_pos, lenC);
    }

    out << ((state[0] == oo) ? (0) : (state[0])) << '\n';
    in.close(), out.close();
    return 0;
}
