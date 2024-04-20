#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1005;
int dp[MAXN][MAXN]{0};
pair<int, int> path[MAXN][MAXN];
int a[MAXN];
int b[MAXN];

void solve(istream &in, std::ostream &out) {
  int n, m;
  in >> n;
  for (size_t i = 1; i <= n; i++) {
    in >> a[i];
  }
  in >> m;
  for (size_t i = 1; i <= m; i++) {
    in >> b[i];
  }
  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= m; j++) {
      if (a[i] == b[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        path[i][j] = {i - 1, j - 1};
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        if (dp[i - 1][j] > dp[i][j - 1]) {
          dp[i][j] = dp[i - 1][j];
          path[i][j] = {i - 1, j};
        } else {
          dp[i][j] = dp[i][j - 1];
          path[i][j] = {i, j - 1};
        }
      }
    }
  }
  int i = n;
  int j = m;
  vector<int> res;
  res.reserve(MAXN);
  while (i != 0 && j != 0) {
    if (path[i][j].first == i - 1 && path[i][j].second == j - 1) {
      res.push_back(a[i]);
    }
    int q = i;
    i = path[i][j].first;
    j = path[q][j].second;
  }
  copy(res.rbegin(), res.rend(), ostream_iterator<int>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"3 1 2 3 3 2 3 1 ", "3 1 2 3 3 3 2 1 "};
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
