#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  size_t n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }

  vector<vector<size_t>> d(n, vector<size_t>(m));
  d[0][0] = a[0][0];
  for (int i = 1; i < m; ++i) {
    d[0][i] = d[0][i - 1] + a[0][i];
  }
  for (int i = 1; i < n; ++i) {
    d[i][0] = d[i - 1][0] + a[i][0];
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      d[i][j] = min(d[i - 1][j], d[i][j - 1]) + a[i][j];
    }
  }
  cout << d[n - 1][m - 1];
  return 0;
}
