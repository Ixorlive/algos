#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct point {
  int x, y;
  bool operator==(const point &other) const {
    return x == other.x && y == other.y;
  }
};
struct point_hash {
  size_t operator()(const point &p) const {
    return hash<int>{}(p.x) ^ (hash<int>{}(p.y) << 1);
  }
};

struct pp {
  bool f = false;
  point p3, p4;
};

pp f(point p1, point p2) {
  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;
  if ((dx ^ dy) & 1) {
    return pp();
  }
  double dxh = dx / 2.0;
  double dyh = dy / 2.0;
  double mx = (p1.x + p2.x) / 2.0;
  double my = (p1.y + p2.y) / 2.0;
  return {true,
          {static_cast<int>(mx + dyh), static_cast<int>(my - dxh)},
          {static_cast<int>(mx - dyh), static_cast<int>(my + dxh)}};
}

void solve(istream &in, std::ostream &out) {
  unordered_set<point, point_hash> ps;
  int n;
  in >> n;
  int x, y;
  int cnt = 1;
  point res[2];
  for (size_t i = 0; i < n; i++) {
    in >> x >> y;
    ps.insert({x, y});
  }
  if (ps.size() == 1) {
    out << 3 << '\n';
    x = ps.begin()->x;
    y = ps.begin()->y;
    out << x - 1 << ' ' << y << '\n'
        << x - 1 << ' ' << y - 1 << '\n'
        << x << ' ' << y - 1;
    return;
  }
  auto update_cnt_three = [&](point p) {
    if (cnt != 3) {
      cnt = 3;
      res[0] = p;
    }
  };
  auto update_cnt_two = [&](point p1, point p2) {
    if (cnt == 1) {
      cnt = 2;
      res[0] = p1;
      res[1] = p2;
    }
  };
  for (auto it1 = ps.begin(); it1 != ps.end(); ++it1) {
    for (auto it2 = std::next(it1); it2 != ps.end(); ++it2) {
      point p1 = {it1->x, it1->y};
      point p2 = {it2->x, it2->y};
      auto rpp = f(p1, p2);
      if (!rpp.f && cnt == 1) {
        if (p1.x > p2.x)
          swap(p1, p2);
        auto q = (p1.y < p2.y ? 1 : -1);
        auto dx = abs(p1.x - p2.x);
        auto dy = abs(p1.y - p2.y);
        point cr1 = {p1.x + q * dy, p1.y - dx},
              cr2 = {p2.x + q * dy, p2.y - dx};
        update_cnt_two(cr1, cr2);
        continue;
      }
      auto f1 = ps.find(rpp.p3) != ps.end(), f2 = ps.find(rpp.p4) != ps.end();
      if (f1 && f2) {
        out << 0;
        return;
      }
      if (f1 || f2) {
        update_cnt_three(f1 ? rpp.p4 : rpp.p3);
      } else {
        update_cnt_two(rpp.p3, rpp.p4);
      }
    }
  }
  if (cnt == 3) {
    out << 1 << '\n' << res[0].x << ' ' << res[0].y;
  } else {
    out << 2 << '\n'
        << res[0].x << ' ' << res[0].y << '\n'
        << res[1].x << ' ' << res[1].y;
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
  vector<string> inputs{
      "2 0 1 1 0 ", "3 0 2 2 0 2 2 ", "4 -1 1 1 1 -1 -1 1 -1 ",
      "12 8 6 -9 6 -4 1 -5 3 6 4 7 -2 9 2 9 8 8 10 -7 -2 -5 -6 1 7",
      "2 25697778 75425596 24381670 -2266860 "};
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
