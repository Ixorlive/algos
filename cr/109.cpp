#include <bits/stdc++.h>

using namespace std;
constexpr int MAXN = 2e2;
constexpr int MAXL = 5e4;
int as[MAXN + 10][MAXL + 10];
#define ll long long

void solve(istream &in, std::ostream &out) {
  int n, l;
  in >> n >> l;
  ll x, d, a, c, m;
  for (size_t i = 0; i < n; i++) {
    in >> x >> d >> a >> c >> m;
    as[i][0] = x;
    for (size_t j = 1; j <= l; j++) {
      x = x + d;
      d = ((a * d + c) % m);
      as[i][j] = x;
    }
    sort(as[i], as[i] + l);
  }
  auto bins = [&](int *a1, int *b1) {
    int s = -1;
    int e = l - 1;
    while (e - s != 1) {
      auto x = (s + e) / 2;
      if (a1[x] - b1[l - x - 2] < 0) {
        s = x;
      } else {
        e = x;
      }
    }
    return min(a1[e], b1[l - e - 1]);
  };
  for (size_t i = 0; i < n - 1; i++) {
    for (size_t j = i + 1; j < n; j++) {
      out << bins(as[i], as[j]) << '\n';
    }
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
  vector<string> inputs{"3 6 1 3 1 0 5 0 2 1 1 100 1 6 8 5 11 "};
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
