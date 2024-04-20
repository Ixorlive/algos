#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MAXN = 1200;

int n;
struct Point {
  int x, y;
};
double getdist(Point &p1, Point &p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}

Point ps[MAXN];
int cols[MAXN];

bool dfs(int *cols, int v, int color, double dist) {
  cols[v] = color;
  for (size_t i = 0; i < n; i++) {
    if (i == v)
      continue;
    if (getdist(ps[v], ps[i]) < dist) {
      if (cols[i] == 0 && !dfs(cols, i, color ^ 3, dist)) {
        return false;
      } else if (cols[i] == cols[v]) {
        return false;
      }
    }
  }
  return true;
}

bool check(double d) {
  memset(cols, 0, sizeof(cols));

  for (size_t i = 0; i < n; i++) {
    if (cols[i] == 0 && !dfs(cols, i, 1, d)) {
      return false;
    }
  }
  return true;
}

void solve(istream &in, std::ostream &out) {
  in >> n;
  int n2 = n * n;
  vector<double> dists(n2);
  for (size_t i = 0; i < n; i++) {
    in >> ps[i].x >> ps[i].y;
  }
  size_t pos = 0;
  for (size_t i = 0; i < n - 1; i++) {
    for (size_t j = i + 1; j < n; j++) {
      dists[pos++] = getdist(ps[i], ps[j]);
    }
  }
  sort(dists.begin(), dists.begin() + pos);
  int l = 0;
  int r = pos - 1;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    if (check(dists[m])) {
      l = m;
    } else {
      r = m - 1;
    }
  }
  check(dists[l]);
  out << fixed << setprecision(8) << dists[l] / 2.0 << '\n';
  for (size_t i = 0; i < n; i++) {
    out << cols[i] << ' ';
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"4 0 0 0 1 1 0 1 1 ", "3 0 0 0 1 0 2 "};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
