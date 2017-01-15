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

ofstream out("fenrir.out");

int main() {
    out << "99\n";
    for (int i = 1; i <= 11; ++i)
        for (int j = 12; j <= 20; ++j)
            out << i << ' ' << j << '\n';

    out.close();
    return 0;
}
