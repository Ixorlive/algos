#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  string s;
  double prev, cur;
  in >> prev;
  double left = 30.0;
  double right = 4000.0;
  for (size_t i = 1; i < n; i++) {
    in >> cur >> s;
    if ((cur < prev && s[0] == 'c') || (cur > prev && s[0] == 'f')) {
      auto mid = fabs(prev + cur) / 2.0;
      right = min(right, mid);
    } else {
      auto mid = fabs(prev + cur) / 2.0;
      left = max(left, mid);
    }
    prev = cur;
  }
  out << fixed << setprecision(6) << left << ' ' << right;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"3 440 220 closer 300 further ",
                        "4 554 880 further 440 closer 622 closer "};
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
