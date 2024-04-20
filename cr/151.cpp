#include <bits/stdc++.h>

using namespace std;

size_t dp[35]{0};

void solve(istream &in, std::ostream &out) {
  int n, k;
  in >> n >> k;
  dp[1] = 1;
  dp[2] = 1;
  for (int i = 3; i <= n; i++) {
    for (int j = max(1, i - k); j < i; j++) {
      dp[i] += dp[j];
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
  vector<string> inputs{"8 2 "};
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
