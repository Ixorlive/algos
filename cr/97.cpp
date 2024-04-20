#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int k;
  in >> k;
  string s;
  in >> s;
  size_t q = 1;
  size_t res = 0;
  for (size_t i = k; i < s.size(); i++) {
    if (s[i] == s[i - k]) {
      res += q;
      ++q;
    } else {
      q = 1;
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
  vector<string> inputs{"2 zabacabab ", "2 abc "};
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
