#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int t;
  in >> t;
  int n;
  int el;
  int len, minv, q;
  int vals[100001];
  for (size_t i = 0; i < t; i++) {
    in >> n >> el;
    minv = el;
    len = 1;
    q = 0;
    for (size_t j = 1; j < n; j++) {
      in >> el;
      if (len + 1 > minv || el <= len) {
        vals[q] = len;
        ++q;
        minv = el;
        len = 0;
      }
      minv = min(el, minv);
      ++len;
    }
    vals[q++] = len;
    out << q << '\n';
    for (size_t j = 0; j < q; j++) {
      out << vals[j] << ' ';
    }
    out << '\n';
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
      " 3 5 1 3 3 3 2 16 1 9 8 7 6 7 8 9 9 9 9 9 9 9 9 9 7 7 2 3 4 3 2 7 "};
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
