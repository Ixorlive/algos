#include <algorithm>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using ll = unsigned long long;

struct point {
  int x, y;
};

// constexpr int MAX_LEN = 40;
constexpr int MAX_LEN = 3 * 100000;

int prefminxs[MAX_LEN * 4];
int prefmaxxs[MAX_LEN * 4];

int sufminxs[MAX_LEN * 4];
int sufmaxxs[MAX_LEN * 4];

int n;

void solve(istream &in, std::ostream &out) {
  ll w, h;
  in >> w >> h >> n;
  point a[MAX_LEN];
  for (size_t i = 0; i < n; i++) {
    in >> a[i].x >> a[i].y;
  }
  sort(a, a + n, [](const point &p1, const point &p2) { return p1.y < p2.y; });
  int helper[MAX_LEN]{0};
  auto yprev = 0;
  size_t k = 1;
  while (k < n) {
    if (a[k].y != a[yprev].y) {
      helper[yprev] = k;
      yprev = k;
    }
    ++k;
  }

  prefmaxxs[0] = a[0].x;
  prefminxs[0] = a[0].x;
  for (size_t i = 1; i < n; ++i) {
    prefminxs[i] = min(a[i].x, prefminxs[i - 1]);
    prefmaxxs[i] = max(a[i].x, prefmaxxs[i - 1]);
  }
  sufmaxxs[n - 1] = a[n - 1].x;
  sufminxs[n - 1] = a[n - 1].x;
  for (int i = n - 2; i >= 0; --i) {
    sufminxs[i] = min(a[i].x, sufminxs[i + 1]);
    sufmaxxs[i] = max(a[i].x, sufmaxxs[i + 1]);
  }

  auto f = [&](int k) {
    int lp = 0;
    int rp = 0;
    int cnt = 1;
    size_t cur = 0;
    bool f = false;
    while (helper[rp] != 0) {
      rp = helper[rp];
      if (a[rp].y - a[0].y >= k) {
        f = true;
        break;
      }
    }
    if (!f)
      return true; // all point in line
    f = false;
    while (helper[cur] != 0) {
      int minleft = cur == 0 ? INT32_MAX : prefminxs[cur - 1];
      int minright = rp > n - 1 ? INT32_MAX : sufminxs[rp];
      int maxleft = cur == 0 ? -1 : prefmaxxs[cur - 1];
      int maxright = rp > n - 1 ? -1 : sufmaxxs[rp];
      auto minx = min(minleft, minright);
      auto maxx = max(maxleft, maxright);
      if (maxx - minx < k) {
        return true;
      }
      if (f)
        break;
      f = true;
      cur = helper[cur];
      if (a[rp].y - a[cur].y < k) {
        while (helper[rp] != 0) {
          rp = helper[rp];
          if (a[rp].y - a[cur].y >= k) {
            f = false;
            break;
          }
        }
        if (f)
          rp = n;
      } else
        f = false;
    }
    return false;
  };
  int l = 1;
  int r = min(w, h);
  while (l <= r) {
    auto m = l + (r - l) / 2;
    if (!f(m)) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  out << l;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 5 6 5 5 4 2 6 4 1 2 3 1 4 ", "4 3 4 1 1 4 3 4 1 1 3 ",
                        "7 9 5 4 1 2 6 5 5 7 7 5 9 "};
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
