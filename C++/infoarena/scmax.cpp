#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 10;

int N;
int BIT[NMAX], Pos[NMAX], From[NMAX], V[NMAX], answer2[NMAX];

const int BUFFER_SIZE = 1 << 20;
class Reader {
    public:
        Reader() {}
        Reader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline Reader & operator >> (int &n) {
            n = 0;
            while(!isdigit(buffer[cursor])) {
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
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

struct Element {
    int value, pos;
    bool operator<(const Element &rhs) const {
        return value == rhs.value ? pos > rhs.pos : value < rhs.value;
    }
} E[NMAX];

void Update(int pos, int value) {
    int cpos = pos;
    for ( ; pos <= N; pos += pos & -pos) {
        if (BIT[pos] < value) {
            BIT[pos] = value;
            Pos[pos] = cpos;
        }
    }
}

pair<int, int> Query(int pos) {
    int ret1 = 0, ret2 = 0;
    for ( ; pos; pos -= pos & -pos) {
        if (BIT[pos] > ret1) {
            ret1 = BIT[pos];
            ret2 = Pos[pos];
        }
    }
    return {ret1, ret2};
}

int main() {
    //assert(freopen("scmax.in", "r", stdin));
    Reader cin("scmax.in");
    assert(freopen("scmax.out", "w", stdout));

    int i;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> E[i].value;
        V[i] = E[i].value;
        E[i].pos = i;
    }
    sort(E + 1, E + N + 1);

    int answer = 0, ans_pos = 0;
    for (i = 1; i <= N; ++i) {
        int best = 0, pos = 0;
        tie(best, pos) = Query(E[i].pos);
        Update(E[i].pos, best + 1);
        if (best + 1 > answer) {
            answer = best + 1;
            ans_pos = E[i].pos;
        }
        From[E[i].pos] = pos;
    }
    cout << answer << '\n';

    int limit = answer;
    answer2[answer--] = ans_pos;
    while (From[ans_pos]) {
        answer2[answer--] = From[ans_pos];
        ans_pos = From[ans_pos];
    }

    for (i = 1; i <= limit; ++i)
        cout << V[answer2[i]] << ' ';
    cout << '\n';

    return 0;
}
