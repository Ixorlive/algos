#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int kM = 1e5 + 10;
int a[kM * 2 + 1];
int z[kM * 2 + 1];
int res[kM];
int n;

void z_function() {
  size_t m = 2 * n + 1;
  for (int i = 1, l = 0, r = 0; i < m; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < m && a[z[i]] == a[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
}

void solve(istream &in, std::ostream &out) {
  int zachem;
  in >> n >> zachem;
  for (size_t i = 0; i < n; i++) {
    in >> a[i];
    a[2 * n - i] = a[i];
  }
  a[n] = 0;
  z_function();
  int k = 0;
  res[k++] = n;
  for (size_t i = 1; i <= n / 2; i++) {
    if (z[2 * n - 2 * i + 1] >= i) {
      res[k++] = n - i;
    }
  }
  for (size_t i = 0; i < k; ++i) {
    out << res[i] << " ";
  }
  // for (int i = k - 1; i >= 0; i--) {
  //   out << res[i] << " ";
  // }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"6 2 1 1 2 2 1 1"};
  for (const auto &input : inputs) {
    istringstream in(input);
    ostringstream out;
    solve(in, out);
    cout << out.str();
  }
}
