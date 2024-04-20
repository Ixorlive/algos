#include <bits/stdc++.h>

using namespace std;

size_t dp[105][6]{0};

void solve(istream &in, std::ostream &out) {
  string ss[6];
  for (size_t i = 0; i < 6; i++) {
    getline(in, ss[i]);
  }
  char c;
  int n;
  in >> c >> n;
  int map[256]{0};
  map['N'] = 0;
  map['S'] = 1;
  map['W'] = 2;
  map['E'] = 3;
  map['U'] = 4;
  map['D'] = 5;
  for (size_t i = 0; i < 6; i++) {
    dp[0][i] = 1;
  }
  for (size_t i = 1; i < n; i++) {
    for (size_t j = 0; j < 6; j++) {
      dp[i][j] = 1;
      for (char c2 : ss[j]) {
        dp[i][j] += dp[i - 1][map[c2]];
      }
    }
  }

  out << dp[n - 1][map[c]];
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"N\nNUSDDUSE\nUEWWD\n\nU\nWED\nS 3 "};
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
