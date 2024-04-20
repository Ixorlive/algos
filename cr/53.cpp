#include <bits/stdc++.h>

using namespace std;

struct rect {
  int x1, y1, x2, y2;
  rect(int x, int y) : x1(x), y1(y), x2(x), y2(y) {}
  rect(int lx1, int ly1, int lx2, int ly2)
      : x1(lx1), x2(lx2), y1(ly1), y2(ly2) {}
  void inter(rect r) {
    x1 = max(x1, r.x1);
    x2 = min(x2, r.x2);
    y1 = max(y1, r.y1);
    y2 = min(y2, r.y2);
  }
  void ext(int t) {
    x1 -= t;
    x2 += t;
    y1 -= t;
    y2 += t;
  }
};

void solve(istream &in, std::ostream &out) {
  int t, d, n;
  in >> t >> d >> n;
  rect cur(0, 0);
  int x, y;
  for (size_t i = 0; i < n; i++) {
    in >> x >> y;
    int xt = x + y;
    int yt = x - y;
    cur.ext(t);
    cur.inter(rect(xt - d, yt - d, xt + d, yt + d));
  }
  vector<pair<int, int>> res;
  res.reserve(1e6);
  for (int x = cur.x1; x <= cur.x2; ++x) {
    for (int y = cur.y1; y <= cur.y2; ++y) {
      if ((x + y) % 2 == 0)
        res.push_back({(x + y) / 2, (x - y) / 2});
    }
  }
  out << res.size() << '\n';
  for (const auto &p : res) {
    out << p.first << ' ' << p.second << '\n';
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
  vector<string> inputs{"2 1 5 0 1 -2 1 -2 3 0 3 2 5 ", "1 1 1 0 0 ",
                        "1 10 1 0 0 "};
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
  } else if (i >= 0 && i < inputs.size()) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  } else {
    cout << "Incorrect test id";
  }
}
