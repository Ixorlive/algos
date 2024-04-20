#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  long n, k, d;
  in >> n >> k >> d;
  if (d == 0) {
    out << n;
    return;
  }
  long t = n * 10;
  size_t i = 0;
  for (; i < 10; i++) {
    if ((t + i) % k == 0) {
      n = t + i;
      break;
    }
  }
  if (i == 10) {
    out << -1;
  } else {
    out << to_string(n) << string(d - 1, '0');
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
  vector<string> inputs{"21 108 1", "5 12 4"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
