#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using ll = long long;
constexpr int MAXN = 210;

struct Player {
  int x, y, v;
};

Player ps[MAXN];

int n;
double d;

struct Circle {
  int x, y;
  double r;
};

struct CIntRes {
  short n;
  double x1, y1;
  double x2, y2;
};

// https://gist.github.com/jupdike/bfe5eb23d1c395d8a0a1a4ddd94882ac
CIntRes intersect(const Circle &c1, const Circle &c2) {
  double cDx = c1.x - c2.x;
  double cDy = c1.y - c2.y;
  double R = sqrt(cDx * cDx + cDy * cDy);
  CIntRes res;
  if (!(fabs(c1.r - c2.r) <= R && R <= c1.r + c2.r)) {
    res.n = 0;
    return res;
  }
  double R2 = R * R;
  double R4 = R2 * R2;
  double a = (c1.r * c1.r - c2.r * c2.r) / (2.0 * R2);
  double r2r2 = (c1.r * c1.r - c2.r * c2.r);
  double c =
      sqrt(2.0 * (c1.r * c1.r + c2.r * c2.r) / R2 - (r2r2 * r2r2) / R4 - 1);

  double fx = (c1.x + c2.x) / 2.0 + a * (c2.x - c1.x);
  double gx = c * (c2.y - c1.y) / 2.0;
  double ix1 = fx + gx;
  double ix2 = fx - gx;

  double fy = (c1.y + c2.y) / 2.0 + a * (c2.y - c1.y);
  double gy = c * (c1.x - c2.x) / 2.0;
  double iy1 = fy + gy;
  double iy2 = fy - gy;
  res.n = (fabs(gy) <= 1e-8 && fabs(gx) <= 1e-8) ? 1 : 2;
  res.x1 = ix1;
  res.x2 = ix2;
  res.y1 = iy1;
  res.y2 = iy2;
  return res;
}

CIntRes prc(const Circle &cl) {
  double a = 0;
  double b = 1;
  double c = cl.y;
  double r = cl.r;
  double EPS = 1e-8;
  double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
  CIntRes res;
  if (c * c > r * r * (a * a + b * b) + EPS)
    res.n = 0;
  else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
    res.n = 1;
    res.x1 = x0 + cl.x;
    res.y1 = y0 + cl.y;
  } else {
    res.n = 2;
    double d = r * r - c * c / (a * a + b * b);
    double mult = sqrt(d / (a * a + b * b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    res.x1 = ax + cl.x;
    res.x2 = bx + cl.x;
    res.y1 = ay + cl.y;
    res.y2 = by + cl.y;
  }
  return res;
}

double getdist(double x1, double y1, double x2, double y2) {
  double dx = x2 - x1;
  double dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}

bool f(double t, double *x, double *y) {
  double xs[2 * MAXN * MAXN];
  double ys[2 * MAXN * MAXN];
  size_t pos = 0;
  auto valid = [](double x, double y) {
    return y >= 0 && getdist(0, 0, x, y) <= d;
  };
  auto add_intersect = [&](CIntRes &r) {
    if (r.n > 0) {
      if (valid(r.x1, r.y1)) {
        xs[pos] = r.x1;
        ys[pos++] = r.y1;
      }
      if (r.n == 2 && valid(r.x2, r.y2)) {
        xs[pos] = r.x2;
        ys[pos++] = r.y2;
      }
    }
  };
  for (size_t i = 0; i < n - 1; i++) {
    Circle c1{ps[i].x, ps[i].y, ps[i].v * t};
    for (size_t j = i + 1; j < n; j++) {
      Circle c2{ps[j].x, ps[j].y, ps[j].v * t};
      auto r = intersect(c1, c2);
      add_intersect(r);
    }
  }
  Circle c1{0, 0, d};
  for (size_t i = 0; i < n; i++) {
    Circle c2{ps[i].x, ps[i].y, ps[i].v * t};
    auto r = intersect(c1, c2);
    add_intersect(r);
    r = prc(c2);
    add_intersect(r);
  }
  xs[pos] = 0;
  ys[pos++] = d;
  xs[pos] = d;
  ys[pos++] = 0;
  xs[pos] = -d;
  ys[pos++] = 0;
  for (size_t i = 0; i < pos; i++) {
    bool flag = true;
    for (size_t j = 0; j < n; j++) {
      double dist = getdist(xs[i], ys[i], ps[j].x, ps[j].y);
      if (dist / static_cast<double>(ps[j].v) < t) {
        flag = false;
        break;
      }
    }
    if (flag) {
      *x = xs[i];
      *y = ys[i];
      return true;
    }
  }
  return false;
}

void solve(istream &in, std::ostream &out) {
  in >> d >> n;
  for (size_t i = 0; i < n; i++) {
    in >> ps[i].x >> ps[i].y >> ps[i].v;
  }
  double l = 0;
  double r = 5050;
  double eps = 0.0001;
  double x, y;
  while (r - l > 2 * eps) {
    double m = (l + r) / 2.0;
    if (f(m, &x, &y)) {
      l = m;
    } else {
      r = m;
    }
  }
  double res = (l + r) / 2.0;
  out << round(res * 1000.0) / 1000.0 << '\n'
      << round(x * 1000.0) / 1000.0 << ' ' << round(y * 1000.0) / 1000.0;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Circle c1, c2;
  // cin >> c1.x >> c1.y >> c1.r >> c2.x >> c2.y >> c2.r;
  // auto r = intersect(c1, c2);
  // if (r.n == 0) {
  //   cout << "no points";
  // } else if (r.n == 1) {
  //   cout << r.x1 << "  " << r.y1;
  // } else {
  //   cout << r.x1 << "  " << r.y1 << '\n';
  //   cout << r.x2 << "  " << r.y2;
  // }
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 10 2 1 1 1 -1 1 1 ", "5 2 -1 1 1 -2 1 2",
                        "1 2 2 3 3 -2 2 2"};
  // vector<string> inputs({"6265505"});
  int i = -1;
  if (i == -1) {
    for (int i = 0; i < inputs.size(); ++i) {
      istringstream in(inputs[i]);
      ostringstream out;
      solve(in, out);
      cout << "+==== Test #" << i + 1 << " ====+\n";
      cout << out.str();
      cout << "\n";
    }
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
