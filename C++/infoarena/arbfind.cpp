#include <fstream>
#include <vector>

using namespace std;

ifstream in("arbfind.in");
ofstream out("arbfind.out");

typedef unsigned int uint;

const int NMAX = 32010, MULT1 = 3, MULT2 = 5;

int N, M;
int first[NMAX], euler[2 * NMAX], prefix[2 * NMAX], eulerM[2 * NMAX], *eulerr;
uint HM1[2 * NMAX], HM2[2 * NMAX], H1[2 * NMAX], H2[2 * NMAX], pw1[2 * NMAX], pw2[2 * NMAX];
bool ok;
vector<int> GM[NMAX], G[NMAX], *GT;

inline void DF(const short node) {
    eulerr[++eulerr[0]] = 1;
    if(ok) {
        first[node] = eulerr[0];
        prefix[eulerr[0]] = 1;
    }

    for(int it = 0; it < (int)GT[node].size(); ++it) DF(GT[node][it]);

    ++eulerr[0];
}

void make_hash(int *euler, uint *hash1, uint *hash2) {
    for (int i = 1; i <= euler[0]; ++i) {
        hash1[i] = hash1[i - 1] * MULT1 + euler[i];
        hash2[i] = hash2[i - 1] * MULT2 + euler[i];
    }
}

int main() {
    int i, nrf, child;

    in >> N;
    for(i = 1; i <= N; ++i) {
        in >> nrf;
        while(nrf--) {
            in >> child;
            GM[i].push_back(child);
        }
    }
    eulerr = eulerM;
    GT = GM;
    DF(1);
    make_hash(eulerM, HM1, HM2);

    in >> M;
    for(i = 1; i <= M; ++i) {
        in >> nrf;
        while(nrf--) {
            in >> child;
            G[i].push_back(child);
        }
    }
    ok = true;
    GT = G;
    eulerr = euler;
    DF(1);
    make_hash(euler, H1, H2);

    pw1[0] =  pw2[0] = 1;
    for (i = 1; i <= max(euler[0], eulerM[0]); ++i) {
        pw1[i] = pw1[i - 1] * MULT1;
        pw2[i] = pw2[i - 1] * MULT2;
    }

    for (i = 1; i <= euler[0]; ++i) prefix[i] += prefix[i - 1];

    int left, right, mid;
    for (i = 1; i <= M; ++i) {
        int pos = first[i], res = -1;

        left = 1, right = min(euler[0] - first[i] + 1, eulerM[0]);
        for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
            if (HM1[mid] == H1[pos + mid - 1] - pw1[mid] * H1[pos - 1] &&
                HM2[mid] == H2[pos + mid - 1] - pw2[mid] * H2[pos - 1]) {
                res = mid;
                left = mid + 1;
            }
            else right = mid - 1;
        }

        out << prefix[pos + res - 1] - prefix[pos - 1] << '\n';
    }

    in.close(), out.close();
    return 0;
}
