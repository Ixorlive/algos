#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
void solve(istream &in, std::ostream &out) {
  int k;
  in >> k;
  long min_x, min_y, max_x, max_y;
  long x, y;
  in >> x >> y;
  min_x = x;
  min_y = y;
  max_x = x;
  max_y = y;
  for (size_t i = 1; i < k; i++) {
    in >> x >> y;
    min_x = min(min_x, x);
    min_y = min(min_y, y);
    max_x = max(max_x, x);
    max_y = max(max_y, y);
  }
  out << min_x << ' ' << min_y << ' ' << max_x << ' ' << max_y;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"4 1 3 3 1 3 5 6 3"};
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
