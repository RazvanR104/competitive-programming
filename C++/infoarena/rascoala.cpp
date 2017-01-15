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

const int BUFFER_SIZE = 1 << 20;

class InputReader {
    public:
        InputReader() {}
        InputReader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline InputReader & operator >> (int &n) {
            n = 0;
            sign = 1;
            while(!isdigit(buffer[cursor])) {
                if (buffer[cursor] == '-') sign = -1;
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            n *= sign;
            return *this;
        }
        inline void close() {
            fclose(file);
        }
    private:
        int cursor, sign;
        char buffer[BUFFER_SIZE];
        FILE* file;
        inline void advance() {
            ++cursor;
            if(cursor == BUFFER_SIZE) {
                cursor = 0;
                fread(buffer, BUFFER_SIZE, 1, file);
            }
        }
};

InputReader in("rascoala.in");
ofstream out("rascoala.out");

const int NMAX = 510, oo = 0x3f3f3f3f;

int P, N, M, K, pos;
int max_ln[NMAX], min_ln[NMAX], max_col[NMAX], min_col[NMAX];
int64 sum[NMAX * NMAX];

struct Elem {
    int ln, col, value;

    bool operator<(const Elem &rhs) const {
        if (value < rhs.value) return true;
        if (value > rhs.value) return false;
        if (ln < rhs.ln) return true;
        if (ln > rhs.ln) return false;
        if (col < rhs.col) return true;
        return false;
    }
} E[NMAX * NMAX];

int Partition(int left, int right) {
    int pivot_index = left + rand() % (right - left + 1);
    swap(E[pivot_index], E[right]);

    int i, pos = left;
    for (i = left; i < right; ++i)
        if (E[i] < E[right])
            swap(E[i], E[pos++]);
    swap(E[right], E[pos]);
    return pos;
}

void QuickSort(int left, int right) {
    if (left >= right) return;

    int pivot = Partition(left, right);
    QuickSort(left, pivot - 1);
    QuickSort(pivot + 1, right);
}

int Distance(int x1, int y1, int x2, int y2) {
    int aux, ret = 0;

    aux = x1 - x2;
    if (aux < 0) aux = -aux;
    ret += aux;

    aux = y1 - y2;
    if (aux < 0) aux = -aux;
    ret += aux;

    return (ret == 0) ? (-oo) : (ret);
}

int main() {
    int i, j;

    in >> P >> N >> M >> K;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            ++pos;
            //ln[pos] = i;
            //col[pos] = j;
            E[pos].ln = i;
            E[pos].col = j;
            in >> E[pos].value;
            //Sorted[pos] = pos;
        }
    }

    //stable_sort(E + 1, E + pos + 1);
    QuickSort(1, pos);

    for (i = 1; i <= pos; ++i)
        sum[i] = sum[i - 1] + E[i].value;

    int left = 1, right = pos, mid;

    int64 S;
    int res, c, res_c;
    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
        S = sum[mid] + K;
        c = S / mid;

        if (c > E[mid].value) {
            res = mid;
            res_c = c;
            left = mid + 1;
        } else right = mid - 1;
    }


    if (P == 1)
        out << res << '\n' << min((int)res_c, (res + 1 <= pos) ? (E[res + 1].value) : (oo)) << '\n';
    else {
        for (i = 1; i <= res; ++i) {
            int ln = E[i].ln;
            int col = E[i].col;
            if (max_ln[ln] == 0 || max_ln[ln] < col) max_ln[ln] = col;
            if (min_ln[ln] == 0 || min_ln[ln] > col) min_ln[ln] = col;

            if (max_col[col] == 0 || max_col[col] < ln) max_col[col] = ln;
            if (min_col[col] == 0 || min_col[col] > ln) min_col[col] = ln;
        }

        pos = 0;

        for (i = 1; i <= N; ++i) {
            if (max_ln[i] == 0) continue;
            E[++pos].ln = i;
            E[pos].col = min_ln[i];
            E[++pos].ln = i;
            E[pos].col = max_ln[i];
        }

        for (i = 1; i <= M; ++i) {
            if (max_col[i] == 0) continue;
            E[++pos].ln = min_col[i];
            E[pos].col = i;
            E[++pos].ln = max_col[i];
            E[pos].col = i;
        }

        int ress = -oo, k;
        for (i = 1; i < pos; ++i) {
            int ln = E[i].ln;
            int col = E[i].col;
            for (k = i + 1; k <= pos; ++k)
                ress = max(ress, Distance(ln, col, E[k].ln, E[k].col));
        }

        out << ress << '\n';
    }
    in.close(), out.close();
    return 0;
}
