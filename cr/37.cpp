#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<array<int, 3>> t(n);
  for (int i = 0; i < n; ++i) {
    cin >> t[i][0] >> t[i][1] >> t[i][2];
  }
  vector<int> dp(n);
  dp[0] = t[0][0];
  if (n == 1) {
    cout << dp[0];
    return 0;
  }
  dp[1] = min(t[1][0] + dp[0], t[0][1]);
  if (n == 2) {
    cout << dp[1];
    return 0;
  }
  dp[2] = min(t[2][0] + dp[1], min(t[1][1] + dp[0], t[0][2]));
  for (int i = 3; i < n; ++i) {
    dp[i] = min(t[i][0] + dp[i - 1],
                min(t[i - 1][1] + dp[i - 2], t[i - 2][2] + dp[i - 3]));
  }
  cout << dp.back();

  return 0;
}
