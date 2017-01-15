#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("oypara.in");
ofstream fout("oypara.out");

int N;
struct Point {
   int x, y;
   Point(int x, int y) : x(x), y(y) {}
   bool operator<(const Point& other) const {
      return (x == other.x ? y < other.y : x < other.x);
   }
};
vector<Point> u, d;

int64_t Area(const Point& a, const Point& b, const Point& c) {
   return int64_t(a.x) * b.y - int64_t(a.y) * b.x +
          int64_t(b.x) * c.y - int64_t(b.y) * c.x +
          int64_t(c.x) * a.y - int64_t(c.y) * a.x;
}

void GetConvexHull(vector<Point>& p, bool rev = false) {
   sort(p.begin(), p.end());
   if (rev)
      reverse(p.begin(), p.end());

   vector<Point> st;
   st.push_back(p[0]);

   for(size_t i = 1; i < p.size(); ++i) {
      while (st.size() > 1 && Area(st[st.size() - 2], st.back(), p[i]) <= 0LL)
         st.pop_back();
      st.push_back(p[i]);
   }

   p.swap(st);
}

int main() {
   fin >> N;
   for (int i = 0; i < N; ++i) {
      int x, y1, y2;
      fin >> x >> y1 >> y2;
      d.emplace_back(x, y1);
      u.emplace_back(x, y2);
   }

   GetConvexHull(d, true);
   GetConvexHull(u);

   int up = 0;
   for (size_t i = 0; i < d.size(); ++up)
      while (i < d.size() && Area(u[up], u[up + 1], d[i]) <= 0LL)
         ++i;
   --up;

   int down = 0;
   while (Area(d[down], d[down + 1], u[up]) > 0LL)
      ++down;

   fout << u[up].x << " " << u[up].y << " " << d[down].x << " " << d[down].y << "\n";
   return 0;
}
