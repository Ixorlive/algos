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
  string s1, s2;
  in >> s1 >> s2;
  if (s1.size() != s2.size()) {
    out << "NO";
    return;
  }
  int st1[256]{0};
  int st2[256]{0};
  for (char c : s1) {
    st1[c]++;
  }
  for (char c : s2) {
    st2[c]++;
  }
  for (size_t i = 0; i < 256; i++) {
    if (st1[i] != st2[i]) {
      out << "NO";
      return;
    }
  }
  out << "YES";
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" dusty study ", "rat bat "};
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
