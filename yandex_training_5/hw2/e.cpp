#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int a, b;
  int g_m = -1;
  int g_i = -1;
  int b_m = -1;
  int b_i = -1;
  vector<int> v, v2;
  v.reserve(5 * 100000);
  v2.reserve(5 * 100000);
  long long h = 0;
  for (size_t i = 0; i < n; i++) {
    in >> a >> b;
    if (a > b) {
      if (g_i == -1 || b > g_m) {
        g_m = b;
        g_i = i + 1;
      }
      h += a - b;
      v.push_back(i + 1);
    } else {
      if (b_i == -1 || a > b_m) {
        b_i = i + 1;
        b_m = a;
      }
      v2.push_back(i + 1);
    }
  }
  long long res = 0;
  if (g_i != -1) {
    res = h + g_m;
  }
  if (b_i != -1) {
    res = max(h + b_m, res);
  }
  out << res << '\n';
  for (size_t i = 0; i < v.size(); i++) {
    if (v[i] != g_i) {
      out << v[i] << ' ';
    }
  }
  if (g_i != -1) {
    out << g_i << ' ';
  }
  if (b_i != -1) {
    out << b_i << ' ';
  }
  for (size_t i = 0; i < v2.size(); i++) {
    if (v2[i] != b_i) {
      out << v2[i] << ' ';
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
  vector<string> inputs{" 3 1 5 8 2 4 4 ", " 2 7 6 7 4 "};
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
