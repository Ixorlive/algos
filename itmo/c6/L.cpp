#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int kN = 1e6 + 10;
int z[3 * kN + 1];
int a[3 * kN + 1];
int n;

void z_function() {
  size_t m = 3 * n + 1;
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
  string s;
  in >> s;
  n = (int)s.length();
  for (size_t i = 0; i < n; i++) {
    int k = s[i] - 'a';
    a[i] = k;
    a[n + 1 + i] = k;
    a[2 * n + i + 1] = k;
  }
  a[n] = -1;
  z_function();
  int pos = 1;
  for (size_t i = n + 2; i < 2 * n + 1; i++) {
    auto t = z[i];
    if (t != n && a[t] > a[i + t])
      ++pos;
  }
  out << pos;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"abracadabra", "cabcab"};
  // vector<string> inputs{"cabcab"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
