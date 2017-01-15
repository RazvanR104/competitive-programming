#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010;

int XP, YP, XG, YG, XF, YF, N, M;
int gox[NMAX], goy[NMAX];
pair<int, int> PV[NMAX], PO[NMAX];

int main() {
    assert(freopen("parc.in", "r", stdin) != NULL);
    assert(freopen("parc.out", "w", stdout) != NULL);

    int i, j;

    cin >> XP >> YP >> XG >> YG >> XF >> YF;

    if (XG > XF) {
        swap(XG, XF);
        swap(YG, YF);
    }

    bool rev = 0;
    if (YG > YF)
        rev = 1;

    cin >> N;
    for (i = 1; i <= N; ++i) {
        cin >> PV[i].first >> PV[i].second;
        if (PV[i].first > PV[i].second)
            swap(PV[i].first, PV[i].second);
    }
    sort(PV + 1, PV + N + 1);

    cin >> M;
    for (i = 1; i <= M; ++i) {
        cin >> PO[i].first >> PO[i].second;
        if (rev) {
            if (PO[i].second > PO[i].first)
                swap(PO[i].second, PO[i].first);
        } else {
            if (PO[i].first > PO[i].second)
                swap(PO[i].second, PO[i].first);
        }
    }
    if (rev)
        sort(PO + 1, PO + M + 1, greater<pair<int, int>>());
    else
        sort(PO + 1, PO + M + 1);

    int dx = abs(XF - XG);
    int dy = abs(YF - YG);

    int left_v = 1, right_v = N;
    while (PV[left_v].first < XG)
        ++left_v;
    while (PV[right_v].second > XF)
        --right_v;

    int left_o = 1, right_o = M;
    if (rev) {
        while (PO[left_o].first > YG)
            ++left_o;
        while (PO[right_o].second < YF)
            --right_o;
    } else {
        while (PO[left_o].first < YG)
            ++left_o;
        while (PO[right_o].second > YF)
            --right_o;
    }

    int sumx = 0, sumy = 0;
    for (i = left_v; i <= right_v; ++i)
        sumx += abs(PV[i].first - PV[i].second);
    for (i = left_o; i <= right_o; ++i)
        sumy += abs(PO[i].first - PO[i].second);

    double answer1 = sqrt((dx - sumx) * (dx - sumx) + (dy - sumy) * (dy - sumy)) + sumx + sumy;
    cout << fixed << answer1 << '\n';

    int rx = abs(dx - sumx);
    int ry = abs(dy - sumy);

    int x = 0, y = 0;
    gox[x++] = PV[left_v].first - XG;
    for (i = left_v; i < right_v; ++i) {
        gox[x] = gox[x - 1] + PV[i + 1].first - PV[i].second;
        ++x;
    }
    //gox[x++] = XF - PV[right_v].second;

    if (rev) {
        goy[y++] = YG - PO[left_o].first;
        for (i = left_o; i < right_o; ++i) {
            goy[y] = goy[y - 1] + PO[i].second - PO[i + 1].first;
            ++y;
        }
        //goy[y++] = PO[right_v].second - YF;
    } else {
        goy[y++] = PO[left_o].first - YG;
        for (i = left_o; i < right_o; ++i) {
            goy[y] = goy[y - 1] + PO[i + 1].first - PO[i].second;
            ++y;
        }
        //goy[y++] = YF - PO[right_o].second;
    }

    i = 0, j = 0;
    int answer2 = 1;
    while (i < x && j < y) {
        if (gox[i] * ry == goy[j] * rx) {
            answer2 *= 2;
            ++i, ++j;
        }
        else if (gox[i] * ry < goy[j] * rx)
            ++i;
        else
            ++j;
    }
    cout << answer2 << '\n';

    return 0;
}
