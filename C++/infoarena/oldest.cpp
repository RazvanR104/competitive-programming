#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

const int BUFFER_SIZE = 1 << 21;

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
            while(!isdigit(buffer[cursor])) {
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            return *this;
        }
    private:
        int cursor;
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

InputReader in("oldest.in");
ofstream out("oldest.out");

const int MOD = 100021;

int N, last_accessed;

vector<pair<int, list<int> > > H[MOD];
map<int, int> access;
set<pair<int, int> > access_sorted;

vector<pair<int, list<int> > >::iterator get_pos(const int value) {
    int pos = value % MOD;

    for (vector<pair<int, list<int> > >::iterator it = H[pos].begin(); it != H[pos].end(); ++it)
        if (it->first == value) return it;

    return H[pos].end();
}

inline void update(const int key) {
    if (access.count(key)) access_sorted.erase(make_pair(access[key], key));

    access[key] = last_accessed;
    access_sorted.insert(make_pair(last_accessed++, key));
}

int main() {
    int op, key, value;

    for (in >> N; N; --N) {
        in >> op;
        if (op == 1) {
            in >> key >> value;

            vector<pair<int, list<int> > >::iterator pos = get_pos(key);

            if (pos != H[key % MOD].end())
                pos->second.push_back(value);
            else {
                H[key % MOD].push_back(make_pair(key, list<int>()));
                H[key % MOD].back().second.push_back(value);
            }

            update(key);
        }
        else {
            set<pair<int, int> >::iterator it = access_sorted.begin();
            vector<pair<int, list<int> > >::iterator _pos = get_pos(it->second);

            out << _pos->second.front() << '\n';
            out.flush();
            _pos->second.pop_front();

            if (_pos->second.size()) update(it->second);
            else access_sorted.erase(it);
        }
    }

    out.close();
    return 0;
}
