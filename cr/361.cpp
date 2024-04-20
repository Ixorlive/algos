#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> g(n);
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
  }
  sort(g.begin(), g.end());

  vector<int> dp(n);
  dp[1] = g[1] - g[0];
  dp[2] = g[2] - g[0];

  for (int i = 3; i < n; ++i) {
    dp[i] = min(dp[i - 1], dp[i - 2]) + g[i] - g[i - 1];
  }

  std::cout << dp.back();

  return 0;
}
