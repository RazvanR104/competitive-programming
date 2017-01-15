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

ifstream in("rrmst.in");
ofstream out("rrmst.out");

const int NMAX = 100010;
const int shear[4][4] = {{1, -1,  0,  2},
                         {2,  0, -1,  1},
                         {1,  1, -2,  0},
                         {0,  2, -1, -1}};

int N;
int sorted[NMAX], nn[NMAX][8], aux[NMAX];
pair<int, int> pt[NMAX], sheared[NMAX];

#define X first
#define Y second

inline int dist(const pair<int, int> &p, const pair<int, int> &q) {
  int dx, dy;

  dx = p.X - q.X;
  if(dx < 0) dx = -dx;
  dy = p.Y - q.Y;
  if(dy < 0) dy = -dy;

  return dx + dy;
}

void Merge(int left, int mid, int right, int oct) {
  int i, j, k, y2;
  int i1;
  int i2;
  int best_i2;
  int best_dist;
  int d;

  i1 = left;
  i2 = mid;
  y2 = pt[sorted[i2]].Y;

  while((i1 < mid) && (pt[sorted[i1]].Y >= y2)) ++i1;

  if(i1 < mid) {
    best_i2 = i2;
    best_dist = dist(pt[sorted[i1]], pt[sorted[best_i2]]);
    i2++;

    while((i1 < mid) && (i2 < right)) {
      if( pt[ sorted[i1] ].Y < pt[ sorted[i2] ].Y )
      {
        d = dist(pt[sorted[i1]], pt[sorted[i2]]);
        if( d < best_dist )
        {
          best_i2   = i2;
          best_dist = d;
        }
        i2++;
      }
      else
      {
        if( (nn[ sorted[i1] ][oct] == -1) ||
            ( best_dist < dist( pt[sorted[i1]], pt[nn[ sorted[i1] ][oct]]) )
           )
        {
          nn[ sorted[i1] ][oct] = sorted[best_i2];
        }
        i1++;
        if( i1 < mid )
        {
          best_dist = dist( pt[sorted[i1]], pt[sorted[best_i2]]);
        }
      }
    }

    while( i1 < mid )
    {
      if( (nn[ sorted[i1] ][oct] == -1) ||
          ( dist( pt[sorted[i1]], pt[sorted[best_i2]] ) <
            dist( pt[sorted[i1]], pt[nn[ sorted[i1] ][oct]]) )
        )
      {
        nn[ sorted[i1] ][oct] = sorted[best_i2];
      }
      i1++;
    }
  }

  oct = (oct + 4) % 8;

  i1 = right - 1;
  i2 = mid - 1;   y2 = pt[ sorted[i2] ].Y;

  while((i1 >= mid) && (pt[sorted[i1]].Y <= y2)) i1--;

  if(i1 >= mid) {
    best_i2 = i2;
    best_dist = dist(pt[sorted[i1]], pt[sorted[best_i2]]);
    i2--;

    while((i1 >= mid) && (i2 >= left)) {
      if(pt[sorted[i1]].Y > pt[sorted[i2]].Y) {
        d = dist(pt[sorted[i1]], pt[sorted[i2]]);
        if(d < best_dist ) {
          best_i2 = i2;
          best_dist = d;
        }
        i2--;
      }
      else
      {
        if( (nn[ sorted[i1] ][oct] == -1) ||
            ( best_dist < dist( pt[sorted[i1]], pt[nn[ sorted[i1] ][oct]]) )
           )
        {
          nn[ sorted[i1] ][oct] = sorted[best_i2];
        }
        i1--;
        if( i1 >= mid )
        {
          best_dist = dist( pt[sorted[i1]], pt[sorted[best_i2]] );
        }
      }
    }

    while( i1 >= mid )
    {
      if( (nn[ sorted[i1] ][oct] == -1) ||
          ( dist( pt[sorted[i1]], pt[sorted[best_i2]] ) <
            dist( pt[sorted[i1]], pt[nn[ sorted[i1] ][oct]]) )
        )
      {
        nn[ sorted[i1] ][oct] = sorted[best_i2];
      }
      i1--;
    }
  }

  i = left;
  j = mid;
  k = left;

  while((i < mid) && (j < right)) {
        if(pt[sorted[i]].Y >= pt[sorted[j]].Y) aux[k++] = sorted[i++];
        else aux[k++] = sorted[j++];
  }

  while(i < mid) aux[k++] = sorted[i++];
  while(j < right) aux[k++] = sorted[j++];

  memcpy(sorted + left, aux + left, (right-left) * sizeof(int));
}

void NE_SW(int left, int right, int oct) {
  int mid;

  if(right == left + 1) nn[sorted[left]][oct] = nn[sorted[left]][(oct+4) % 8] = -1;
  else {
    mid = (left + right) / 2;
    NE_SW(left, mid, oct);
    NE_SW(mid, right, oct);
    Merge(left, mid, right, oct);
  }
}

struct Compare {
    bool operator()(const int &lhs, const int &rhs) {
        if (sheared[lhs].X < sheared[rhs].X) return true;
        if (sheared[lhs].X > sheared[rhs].X) return false;
        if (sheared[lhs].Y < sheared[rhs].Y) return true;
        return false;
    }
};

void Compute_Neighbors() {
  int i, oct;

  for(oct = 0; oct < 4; ++oct) {
        for(i = 0; i < N; ++i) {
            sheared[i].X = shear[oct][0] * pt[i].X + shear[oct][1] * pt[i].Y;
            sheared[i].Y = shear[oct][2] * pt[i].X + shear[oct][3] * pt[i].Y;
            sorted[i] = i;
        }

    sort(sorted, sorted + N, Compare());
    NE_SW(0, N, oct);
  }
}

vector<pair<int, int> > Edges;
struct CompareEdges {
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
        if (dist(pt[lhs.X], pt[lhs.Y]) < dist(pt[rhs.X], pt[rhs.Y])) return true;
        return false;
    }
};

int LL[NMAX], height[NMAX];

int get_root(int pos) {
    int ret, x, y;
    for (ret = pos; ret != LL[ret]; ret = LL[ret]);

    x = pos;
    while(x != LL[x]) {
        y = LL[x];
        LL[x] = ret;
        x = y;
    }

    return ret;
}

void unite(int first, int second) {
    if (height[first] > height[second]) LL[second] = first;
    else {
        LL[first] = second;
        if (height[first] == height[second]) ++height[second];
    }
}

int main() {
    int i, j;
    int64 res = 0;

    in >> N;
    for (i = 0; i < N; ++i) in >> pt[i].X >> pt[i].Y;

    Compute_Neighbors();

    for (i = 0; i < N; ++i)
        for (j = 0; j < 8; ++j) {
            if (nn[i][j] == -1) continue;
            Edges.push_back(make_pair(i, nn[i][j]));
        }
    sort(Edges.begin(), Edges.end(), CompareEdges());

    for (i = 0; i < N; ++i) LL[i] = i;

    for (i = 0; i < (int)Edges.size(); ++i) {
        int stroot = get_root(Edges[i].X), ndroot = get_root(Edges[i].Y);
        if (stroot == ndroot) continue;
        unite(stroot, ndroot);
        res += dist(pt[Edges[i].X], pt[Edges[i].Y]);
        out << Edges[i].X << ' ' << Edges[i].Y << '\n';
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
