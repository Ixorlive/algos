#include <bits/stdc++.h>

using namespace std;

void solve(istream &in, std::ostream &out) {
  string s;
  in >> s;
  map<char, size_t> res;
  int n = s.size();
  for (size_t i = 0; i < n; i++) {
    auto right = n - i;
    auto left = i + 1;
    res[s[i]] += right * left;
  }
  for (const auto &[c, r] : res) {
    out << c << ": " << r << '\n';
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
  vector<string> inputs{"hello"};
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
