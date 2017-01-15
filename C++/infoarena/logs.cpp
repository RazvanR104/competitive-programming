#include <fstream>
#include <cstring>

using namespace std;

ifstream in("logs.in");
ofstream out("logs.out");

const int MMAX = 1510, NMAX = 15010;

int N, M;
int longest[MMAX], num[NMAX], psorted[MMAX], plast_sorted[MMAX];
char line[MMAX];

int main() {
    int i, j, res = 0, pos = 0;
    int *sorted = psorted, *last_sorted = plast_sorted;
    in >> N >> M;
    in.getline(line, MMAX);

    for (i = 1; i <= N; ++i) {
        in.getline(line + 1, M + 1);
        for (j = 1; j <= M; ++j) {
            if (line[j] == '0') longest[j] = 0;
            else ++num[++longest[j]];
        }

        int last_pos = pos;
        pos = M;
        for (j = M; j >= 1; --j) {
            if (j <= last_pos) last_sorted[j] = 0;
            ++last_sorted[j];
            if (num[last_sorted[j]]) {
                sorted[pos--] = last_sorted[j];
                --num[last_sorted[j]];
            }
        }

        for (j = M; j > pos; --j)
            res = max(res, (M - j + 1) * sorted[j]);

        swap(sorted, last_sorted);
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
