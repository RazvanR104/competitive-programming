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

ifstream in("heapuri.in");
ofstream out("heapuri.out");

const int NMAX = 200010;

int N, LEN, pos;
int HEAP[NMAX], NUM[NMAX], POS[NMAX];

void sift(int size, int pos) {
    int son;
    do {
        son = 0;
        if (pos * 2 <= size) {
            son = pos * 2;
            if (pos * 2 + 1 <= size && NUM[HEAP[pos * 2 + 1]] < NUM[HEAP[pos * 2]]) son = pos * 2 + 1;
            if (son > size) son = 0;
        }

        if (son) {
            swap(HEAP[pos], HEAP[son]);
            POS[HEAP[pos]] = pos;
            POS[HEAP[son]] = son;
            pos = son;
        }
    }
    while(son);
}

void percolate(int size, int pos) {
    int key = HEAP[pos];

    while(pos > 1 && NUM[key] < NUM[HEAP[pos / 2]]) {
        HEAP[pos] = HEAP[pos / 2];
        POS[HEAP[pos]] = pos;
        pos /= 2;
    }

    HEAP[pos] = key;
    POS[HEAP[pos]] = pos;
}

int main() {
    int operation, num;

    in >> N;
    while(N--) {
        in >> operation;
        if (operation == 1) {
            in >> num;
            NUM[++pos] = num;
            HEAP[++LEN] = pos;
            POS[pos] = LEN;
            percolate(LEN, LEN);
        }
        else if (operation == 2) {
            in >> num;
            NUM[num] = -1;
            percolate(LEN, POS[num]);
            POS[HEAP[1]] = 0;
            HEAP[1] = HEAP[LEN--];
            POS[HEAP[1]] = 1;
            if (LEN > 1) sift(LEN, 1);
        }
        else out << NUM[HEAP[1]] << '\n';
    }

    in.close(), out.close();
    return 0;
}
