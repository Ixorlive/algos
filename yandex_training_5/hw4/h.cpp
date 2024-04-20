#include <algorithm>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using ll = long long;
constexpr int MAXN = 100005;

struct Party {
  ll v, p, ind;
};

Party ps[MAXN];
int n;

void solve(istream &in, std::ostream &out) {
  in >> n;
  for (size_t i = 0; i < n; i++) {
    in >> ps[i].v >> ps[i].p;
    ps[i].ind = i;
  }
  sort(ps, ps + n, [](const Party &p, const Party &p2) { return p.v > p2.v; });
  ll sum = 0;
  ll num_voices[MAXN];
  for (size_t i = 0; i < n; i++) {
    sum += ps[i].v;
    num_voices[i] = sum - (i + 1) * ps[i].v;
  }
  ll prs[MAXN];
  prs[0] = ps[0].v + (n > 1 && ps[0].v == ps[1].v ? 1 : 0);
  ll l, r, d, q;
  auto bs = [&](int i) {
    l = 0;
    r = i;
    while (l < r - 1) {
      auto m = l + (r - l) / 2;
      if (num_voices[m] + ps[i].v > ps[m].v) {
        r = m;
      } else {
        l = m;
      }
    }
    auto val = ps[i].v + num_voices[l];
    auto df = ps[l].v - val;
    auto t = l + 1;
    d = df / (t + 1);
    q = df % (t + 1);
    q = q < t ? q + 1 : t;
    val += d * t + q;
    return val;
  };
  for (size_t i = 1; i < n; i++) {
    prs[i] = bs(i);
  }
  int minx = -1;
  int res_ind;
  for (size_t i = 0; i < n; i++) {
    if (ps[i].p == -1) {
      continue;
    }
    auto v = prs[i] - ps[i].v + ps[i].p;
    if (minx == -1 || v < minx) {
      minx = v;
      res_ind = i;
    }
  }
  ll res[MAXN];
  if (res_ind == 0) {
    out << minx << '\n' << ps[0].ind + 1 << '\n';
    for (size_t i = 0; i < n; i++) {
      res[ps[i].ind] = ps[i].v;
    }
    if (prs[0] > res[ps[0].ind]) {
      ++res[ps[0].ind];
      --res[ps[1].ind];
    }
    copy(res, res + n, ostream_iterator<ll>(out, " "));
    return;
  }
  auto bsres = bs(res_ind);
  out << minx << '\n' << ps[res_ind].ind + 1 << '\n';
  for (size_t i = 0; i < n; i++) {
    res[ps[i].ind] = ps[i].v;
  }
  for (size_t i = 0; i <= l; i++) {
    res[ps[i].ind] = res[ps[l].ind] - d;
  }
  for (size_t i = 0; i < q; i++) {
    res[ps[i].ind]--;
  }
  res[ps[res_ind].ind] = bsres;
  copy(res, res + n, ostream_iterator<ll>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 3 7 -1 2 8 1 2 "};
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
