#include <bits/stdc++.h>

using namespace std;

size_t dp[1005];

void solve(istream &in, std::ostream &out) {
  int n, a, b;
  in >> n >> a >> b;
  dp[1] = 0;
  for (size_t i = 2; i <= n; i++) {
    for (size_t j = 1; j < i; j++) {
      auto r = max(dp[j] + a, dp[i - j] + b);
      if (j == 1 || dp[i] > r)
        dp[i] = r;
    }
  }
  out << dp[n];
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"8 1 1 "};
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
