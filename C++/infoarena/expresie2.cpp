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

ifstream in("expresie2.in");
ofstream out("expresie2.out");

const int LMAX = 100010, oo = 0x3f3f3f3f;

int pos, res;
char str[LMAX];

int Solve_1(); //w/o '()' or '[]'
int Solve_2(); //'()'
int Solve_3(); //'[]'

int Solve_3() {
    int nr, sign;
    vector<int> values;

    while(str[pos] != ']') {
        if (str[pos] == ',' || str[pos] == '-') ++pos;
        else if (str[pos] >= '0' && str[pos] <= '9') {
            ++res;
            nr = 0;
            sign = 1;
            if (pos > 0 && str[pos - 1] == '-') sign = -1;

            while (str[pos] >= '0' && str[pos] <= '9')
                nr = nr * 10 + str[pos++] - '0';

            nr *= sign;
            values.push_back(nr);
        }
        else if (str[pos] == '(') {
            ++pos;
            values.push_back(Solve_2());
            ++pos;
        }
        else if (str[pos] == '[') {
            ++pos;
            values.push_back(Solve_3());
            ++pos;
        }
    }

    sort(values.begin(), values.end());

    return values[(values.size() + 1) / 2 - 1];
}

int Solve_2() {
    int sum = 0, ret = -oo, nr, sign;

    while(str[pos] != ')') {
        if (str[pos] == ',' || str[pos] == '-') ++pos;
        else if (str[pos] >= '0' && str[pos] <= '9') {
            ++res;
            nr = 0;
            sign = 1;
            if (pos > 0 && str[pos - 1] == '-') sign = -1;

            while (str[pos] >= '0' && str[pos] <= '9')
                nr = nr * 10 + str[pos++] - '0';

            nr *= sign;

            sum += nr;
            ret = max(ret, sum);

            if (sum < 0) sum = 0;
        }
        else if (str[pos] == '(') {
            ++pos;
            sum += Solve_2();
            ret = max(ret, sum);
            ++pos;

            if (sum < 0) sum = 0;
        }
        else if (str[pos] == '[') {
            ++pos;
            sum += Solve_3();
            ret = max(ret, sum);
            ++pos;

            if (sum < 0) sum = 0;
        }
    }

    return ret;
}

int Solve_1() {
    int nr, sign, ret = 0;

    while (str[pos]) {
        if (str[pos] == ',' || str[pos] == '-') ++pos;
        else if (str[pos] >= '0' && str[pos] <= '9') {
            ++res;
            nr = 0;
            sign = 1;
            if (pos > 0 && str[pos - 1] == '-') sign = -1;

            while (str[pos] >= '0' && str[pos] <= '9')
                nr = nr * 10 + str[pos++] - '0';

            nr *= sign;
            ret += nr;
        }
        else if (str[pos] == '(') {
            ++pos;
            ret += Solve_2();
            ++pos;
        }
        else if (str[pos] == '[') {
            ++pos;
            ret += Solve_3();
            ++pos;
        }
    }

    return ret;
}

int main() {
    in >> str;
    out << res << '\n' << Solve_1() << '\n';

    in.close(), out.close();
    return 0;
}
