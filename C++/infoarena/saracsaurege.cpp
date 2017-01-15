#include <fstream>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 1 << 10;

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

InputReader in("saracsaurege.in");
ofstream out("saracsaurege.out");

const int NMAX = 50010, LG = 3;

int N, M;
int RMQ[LG][NMAX];

inline int lg2(int value) {
    int ret = -1;
    while(value) ++ret, value >>= 1;
    return ret;
}

inline int pw2(int expo) {
    return (1 << expo);
}

void compute(int *source, int *dest, int prev_lg) {
    for (int i = 1; i + pw2(prev_lg) <= N; ++i)
        dest[i] = max(source[i], source[i + pw2(prev_lg)]);
}

void newlg(int &curr_lg, int lgdist) {
    while(curr_lg < lgdist) {
        compute(RMQ[1], RMQ[2], curr_lg);
        memcpy(RMQ[1], RMQ[2], sizeof(RMQ[1]));
        ++curr_lg;
    }
}

int main() {
    int i, a, b, curr_lg = 0;

    in >> N >> M;
    for (i = 1; i <= N; ++i) {
        in >> RMQ[0][i];
        RMQ[1][i] = RMQ[0][i];
    }

    while(M--) {
        in >> a >> b;
        int lgdist = lg2(b - a + 1);
        if (curr_lg <= lgdist) {
            newlg(curr_lg, lgdist);
            out << max(RMQ[1][a], RMQ[1][b - pw2(lgdist) + 1]) << '\n';
        }
        else {
            curr_lg = 0;
            memcpy(RMQ[1], RMQ[0], sizeof(RMQ[1]));
            newlg(curr_lg, lgdist);
            out << max(RMQ[1][a], RMQ[1][b - pw2(lgdist) + 1]) << '\n';
        }
    }

    in.close(), out.close();
    return 0;
}
