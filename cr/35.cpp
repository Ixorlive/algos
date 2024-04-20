#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n, m;
  size_t dp[16][51];
  in >> m >> n;
  for (size_t i = 0; i < n; i++) {
    dp[i][0] = 1;
  }
  for (size_t i = 0; i < m; i++) {
    dp[0][i] = 1;
  }
  for (size_t i = 1; i < n; i++) {
    for (size_t j = 1; j < m; j++) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + dp[i - 1][j - 1];
    }
  }
  out << dp[n - 1][m - 1];
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
