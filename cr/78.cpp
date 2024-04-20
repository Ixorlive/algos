#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  size_t k1, m, k2, p2, n2;
  in >> k1 >> m >> k2 >> p2 >> n2;
  constexpr int MAXA = 1000000;
  size_t a;
  int p1 = -1, n1 = -1;
  for (a = 1; a <= MAXA; a++) {
    auto p = (k2 - 1) / (m * a) + 1;
    auto kt = (k2 - 1) % (m * a) + 1;
    auto n = (kt - 1) / a + 1;
    if (p == p2 && n == n2) {
      auto p1t = (k1 - 1) / (m * a) + 1;
      auto k1t = (k1 - 1) % (m * a) + 1;
      auto n1t = (k1t - 1) / a + 1;
      if (n1 == -1) {
        n1 = n1t;
        p1 = p1t;
      } else {
        if (n1 != n1t)
          n1 = 0;
        if (p1 != p1t)
          p1 = 0;
      }
    }
  }
  out << p1 << ' ' << n1;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"89 20 41 1 11 ", "11 1 1 1 1 ", "3 2 2 2 1 "};
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
