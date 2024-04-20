
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int buf[10 * 10]{0};
  int x, y;
  auto ind = [](int x, int y) { return x * 10 + y; };
  for (size_t i = 0; i < n; i++) {
    in >> x >> y;
    buf[ind(x, y)] = 1;
  }
  int res = 0;
  for (size_t i = 1; i <= 8; i++) {
    for (size_t j = 1; j <= 8; j++) {
      if (buf[ind(i, j)] == 1) {
        res += 4 - (buf[ind(i - 1, j)] + buf[ind(i + 1, j)] +
                    buf[ind(i, j - 1)] + buf[ind(i, j + 1)]);
      }
    }
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
  vector<string> inputs{" 3 1 1 1 2 2 1 "};
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
