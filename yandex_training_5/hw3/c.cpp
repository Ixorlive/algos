#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n, a;
  in >> n;
  int s1[100005]{0};
  int s2[100005]{0};
  int m = 0;
  for (size_t i = 0; i < n; i++) {
    in >> a;
    s1[a]++;
    s2[a]++;
    if (a > 0) {
      s1[a - 1]++;
    }
    s2[a + 1]++;
  }
  for (size_t i = 0; i < 100005; i++) {
    m = max({m, s1[i], s2[i]});
  }
  out << n - m;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"5 1 2 3 4 5", "10 1 1 2 3 5 5 2 2 1 5"};
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
