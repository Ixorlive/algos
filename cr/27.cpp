#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  int a[101];
  a[1] = 1;
  int cur = 1;
  while (a[cur] <= n) {
    ++cur;
    a[cur] = cur * cur * cur;
  }

  int k = 1;
  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[k + 1] <= i) {
      ++k;
    }
    dp[i] = dp[i - 1] + 1;
    for (int j = 2; j <= k; ++j) {
      dp[i] = min(dp[i], dp[i - a[j]] + 1);
    }
  }

  cout << dp[n];

  return 0;
}
