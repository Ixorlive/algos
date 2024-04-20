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
  bool operator==(const point &p2) const { return x == p2.x && y == p2.y; }
};

struct point_hash {
  size_t operator()(const point &p) const {
    int x = p.x + 20000;
    int y = p.y + 20000;
    return x * 30001 + y;
  }
};

struct segment {
  int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

  segment() = default;
  segment(int x1l, int y1l, int x2l, int y2l) {
    if (x1l < x2l || (x1l == x2l && y1l < y2l)) {
      x1 = x1l;
      y1 = y1l;
      x2 = x2l;
      y2 = y2l;
    } else {
      x1 = x2l;
      y1 = y2l;
      x2 = x1l;
      y2 = y1l;
    }
  }

  bool operator==(const segment &other) const {
    return x1 == other.x1 && x2 == other.x2 && y1 == other.y1 && y2 == other.y2;
  }
};

segment pics[1001];

point norm_seg(const segment &seg) {
  return {seg.x2 - seg.x1, seg.y2 - seg.y1};
}
void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int x1, x2, y1, y2;
  unordered_map<point, vector<point>, point_hash> m;
  for (size_t i = 0; i < n; i++) {
    in >> x1 >> y1 >> x2 >> y2;
    segment s(x1, y1, x2, y2);
    auto p = norm_seg(s);
    if (m.find(p) == m.end()) {
      m[p] = vector<point>();
      m[p].reserve(1000);
    }
    m[p].push_back({s.x1, s.y1});
  }
  for (size_t i = 0; i < n; i++) {
    in >> x1 >> y1 >> x2 >> y2;
    pics[i] = segment(x1, y1, x2, y2);
  }
  unordered_map<point, size_t, point_hash> s;
  size_t mmax = 0;
  for (const auto &bseg : pics) {
    auto nseg = norm_seg(bseg);
    auto it = m.find(nseg);
    if (it == m.end()) {
      continue;
    }
    const auto &suit = it->second;
    for (const auto &aseg : suit) {
      mmax = max(++s[{bseg.x1 - aseg.x, bseg.y1 - aseg.y}], mmax);
    }
  }
  out << n - mmax;
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
      "5 0 0 1 2 1 0 0 2 2 0 2 2 4 0 3 2 4 0 5 2 9 -1 10 1 10 1 9 3 8 1 10 1 8 "
      "1 9 -1 8 1 9 3 ",
      "1 3 4 7 9 -1 3 3 8 ", "1 -4 5 2 -3 -12 4 -2 4 "};
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
