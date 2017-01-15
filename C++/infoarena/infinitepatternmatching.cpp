#include <bits/stdc++.h>

using namespace std;

const int BMAX = 100;
typedef uint64_t i64;

const i64 inf = 0xffffffffffffffffLL;
i64 V[BMAX];
char B[BMAX];

int Zeroes(const vector<int> &V) {
    int res = 0;
    for (auto it : V) {
        if (it == 0)
            ++res;
    }
    return res;
}

i64 Transform_v2(const vector<int> &V) {
    int pw = 0;
    i64 res = 0;
    for (auto it : V) {
        if (it == 1)
            res |= (1LL << pw);
        ++pw;
    }
    return res;
}

int LastZeroes(const vector<int> &V) {
    int res = 0;
    for (auto it : V) {
        if (it != 0)
            break;
        ++res;
    }
    return res;
}

int Ones(const vector<int> &V)  {
    int res = 0;
    for (auto it : V) {
        if (it == 1)
            ++res;
    }
    return res;
}

int Check(int pos, i64 value) {
    int BIT[BMAX];
    BIT[0] = 0;
    while (value) {
        BIT[++BIT[0]] = (value & 1);
        value >>= 1;
    }
    reverse(BIT + 1, BIT + BIT[0] + 1);
    for (int i = 1; i <= BIT[0] && B[pos + i - 1]; ++i) {
        if (B[pos + i - 1] != BIT[i] + '0')
            return -1;
    }

    return pos + BIT[0];
}

i64 Transform(int lo, int hi) {
    i64 res = 0;
    int pw = 0;
    for ( ; hi >= lo; --hi) {
        if (B[hi] == '1')
            res |= (1LL << pw);
        ++pw;
    }
    return res;
}

i64 Result(i64 num, int after) {
    i64 _num = num;
    int bits = 0;
    while (_num) {
        ++bits;
        _num >>= 1;
    }

    i64 res = V[bits - 1] + (num - (1LL << (bits - 1)) + 1) * bits;
    return res + after;
}

int main() {
    ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen("infinitepatternmatching.in", "r", stdin);
    freopen("infinitepatternmatching.out", "w", stdout);
    freopen("debug.err", "w", stderr);
    #endif

    cin >> B;
    int len = strlen(B), i, j;

    for (i = 1; i <= 55; ++i)
         V[i] = V[i - 1] + i * (1LL << (i - 1));

    bool only_zeroes = 1;
    for (i = 0; i < len; ++i) {
        if (B[i] != '0') {
            only_zeroes = 0;
            break;
        }
    }

    if (only_zeroes) {
        cout << Result((1LL << len), 0) << '\n';
        return 0;
    }

    i64 case1 = inf;
    if (B[0] == '1') {
        int pw = len - 1;
        i64 now = 0;
        for (i = 0; i < len; ++i) {
            if (B[i] == '1')
                now |= (1LL << pw);
            --pw;
        }
        case1 = min(case1, Result(now, 0));
    }

    i64 case2 = inf;
    for (i = 1; i < len; ++i) {
        if (B[i] == '0')
            continue;
        vector<int> left, right;
        for (j = i - 1; j >= 0; --j) {
            if (B[j] == '1')
                left.push_back(1);
            else
                left.push_back(0);
        }
        for (j = len - 1; j >= i; --j) {
            if (B[j] == '1')
                right.push_back(1);
            else
                right.push_back(0);
        }

        if (Ones(left) == left.size()) {
            int rz = LastZeroes(right);
            if (rz < left.size())  {
                int diff = left.size() - rz;
                while (diff--)
                    right.insert(right.begin(), 0);
            }
            i64 value = Transform_v2(right);
            case2 = min(case2, Result(value - 1, len - i));
        } else {
            int pos = 0;
            while (left[pos] == 1) {
                left[pos++] = 0;
            }
            left[pos] = 1;

            while (right.size() <= left.size())
                right.insert(right.begin(), -1);

            int match = 0;
            while (match == 0) {
                match = 1;
                for (j = 0; j < left.size(); ++j) {
                    if (right[j] == -1)
                        continue;
                    if (left[j] != right[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match == 0)
                    right.insert(right.begin(), -1);
            }

            for (j = 0; j < left.size(); ++j) {
                if (right[j] != -1)
                    break;
                right[j] = left[j];
            }
            i64 value = Transform_v2(right);
            case2 = min(case2, Result(value - 1, len - i));
        }
    }

    i64 case3 = inf;

    for (i = 0; i < len; ++i) {
        if (B[i] == '0')
            continue;
        for (j = i; j < len; ++j) {
            i64 num = Transform(i, j);

            //check start
            i64 _num = num - 1;
            if (_num <= 0 && i > 0)
                continue;
            int pos = i - 1;
            int match = 1;
            while (pos >= 0 && _num) {
                if ((_num & 1) != i64(B[pos] - '0')) {
                    match = 0;
                    break;
                }
                --pos;
                _num >>= 1;
            }

            if (_num == 0 && pos >= 0)
                match = 0;


            if (!match)
                continue;
            //start done

            _num = num;

            //inside + ending
            pos = i;
            while (pos != -1 && pos < len) {
                pos = Check(pos, num++);
            }
            if (pos == -1)
                continue;
            //inside + ending done

            case3 = min(case3, Result(_num - 1, len - i));
        }
    }

    cout << min(case1, min(case2, case3)) << '\n';

    return 0;
}
