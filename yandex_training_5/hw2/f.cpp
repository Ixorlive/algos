#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  int vals[101];
  in >> n;
  for (size_t i = 0; i < n; i++) {
    in >> vals[i];
  }
  int a, b, k;
  in >> a >> b >> k;
  int l = a / k - (a % k == 0);
  int r = b / k - (b % k == 0);
  if (r - l >= n) {
    out << *max_element(vals, vals + n);
    return;
  }
  int res = -1;
  for (int i = l, j = l % n; i != r + 1; ++i, ++j) {
    if (j == n)
      j %= n;
    res = max(res, vals[j]);
  }
  int j = l % n == 0 ? 0 : n - (l % n);
  for (int i = l; i != r + 1; ++i, --j) {
    if (j < 0)
      j = n - 1;
    res = max(res, vals[j]);
  }
  out << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 5 1 2 3 4 5 3 5 2 ", " 5 1 2 3 4 5 15 15 2 ",
                        " 5 5 4 3 2 1 2 5 2 "};
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
