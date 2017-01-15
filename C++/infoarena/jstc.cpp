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

ifstream in("jstc.in");
ofstream out("jstc.out");

const int NMAX = 1000010, LMAX = 10000010;

int A, B, X, NRI;
int nxt[NMAX], ST[NMAX];
char op[LMAX];

int main() {
    int pos = 0, curi = 1, STpos = 0;
    int64 res = 0;

    in >> A >> B;
    in.getline(op, LMAX);
    in.getline(op, LMAX);

    while(op[pos]) {
        if (op[pos] == 'I') {
            ST[++STpos] = curi;
            nxt[curi] = curi;
            if (STpos > 1 && nxt[ST[STpos - 1]] != ST[STpos - 1]) nxt[ST[STpos - 1]] = curi;
            ++NRI, ++curi;
        } else if (op[pos] == 'E') nxt[ST[STpos--]] = curi;
        else {
            X = (1LL * A * X + B) % NRI + 1;
            int CX = X, update, Y;
            while (nxt[CX] != CX && nxt[CX] < ST[STpos]) CX = nxt[CX];
            update = nxt[CX];

            CX = X;
            while (nxt[CX] != CX && nxt[CX] < ST[STpos]) {
                Y = nxt[CX];
                nxt[CX] = update;
                CX = Y;
            }

            res += (update <= ST[STpos]) ? (update) : (-1);
        }
        ++pos;
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
