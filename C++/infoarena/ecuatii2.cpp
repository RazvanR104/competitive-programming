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

ifstream in("ecuatii2.in");
ofstream out("ecuatii2.out");

const int LMAX = 260;

int N;
char str[LMAX];

int main() {
    int i, lhs_x, lhs_value, rhs_x, rhs_value, sign, nr;

    in >> N;
    in.getline(str, LMAX);

    while(N--) {
        in.getline(str, LMAX);
        lhs_x = lhs_value = rhs_x = rhs_value = 0;
        for (sign = 1, i = 0; str[i] != '='; ) {
            if (str[i] >= '0' && str[i] <= '9') {
                nr = 0;
                while(str[i] >= '0' && str[i] <= '9')
                    nr = nr * 10 + str[i++] - '0';
                if (str[i] == 'x') {
                    lhs_x += nr * sign;
                    ++i;
                }
                else lhs_value += nr * sign;
            } else if (str[i] == 'x') {
                lhs_x += sign;
                ++i;
            } else if (str[i] == '-') {
                sign = -1;
                ++i;
            } else {
                sign = 1;
                ++i;
            }
        }

        for (sign = 1, ++i; str[i]; ) {
            if (str[i] >= '0' && str[i] <= '9') {
                nr = 0;
                while(str[i] >= '0' && str[i] <= '9')
                    nr = nr * 10 + str[i++] - '0';
                if (str[i] == 'x') {
                    rhs_x += nr * sign;
                    ++i;
                }
                else rhs_value += nr * sign;
            } else if (str[i] == 'x') {
                rhs_x += sign;
                ++i;
            } else if (str[i] == '-') {
                sign = -1;
                ++i;
            } else {
                sign = 1;
                ++i;
            }
        }

        lhs_x -= rhs_x;
        rhs_value -= lhs_value;

        if (rhs_value == 0 && lhs_x == 0) out << "infinit\n";
        else if (lhs_x == 0) out << "imposibil\n";
        else out << fixed << setprecision(4) << (double)rhs_value / lhs_x << '\n';
    }

    in.close(), out.close();
    return 0;
}
