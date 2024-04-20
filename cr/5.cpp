#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 100;
constexpr int INF = 1e9;

size_t dp[MAXN + 2][MAXN + 2];
pair<int, int> path[MAXN + 2][MAXN + 2];
int a[MAXN + 1];

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  if (n == 0) {
    out << 0 << '\n' << 0 << ' ' << 0;
    return;
  }
  a[0] = 0;
  for (size_t i = 1; i <= n; i++) {
    in >> a[i];
  }
  memset(dp, 1, sizeof(dp));
  dp[0][0] = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n + 1; j++) {
      if (j < n && a[i + 1] > 100 && dp[i][j] + a[i + 1] < dp[i + 1][j + 1]) {
        dp[i + 1][j + 1] = dp[i][j] + a[i + 1];
        path[i + 1][j + 1] = {i, j};
      }
      if (a[i + 1] <= 100 && dp[i][j] + a[i + 1] < dp[i + 1][j]) {
        dp[i + 1][j] = dp[i][j] + a[i + 1];
        path[i + 1][j] = {i, j};
      }
      if (j > 0 && dp[i][j] < dp[i + 1][j - 1]) {
        dp[i + 1][j - 1] = dp[i][j];
        path[i + 1][j - 1] = {i, j};
      }
    }
  }
  int mmin = -1, k1, k2;
  for (size_t i = 0; i < n + 1; i++) {
    if (mmin == -1 || dp[n][i] <= mmin) {
      mmin = dp[n][i];
      k1 = i;
    }
  }
  int cur_d = n;
  int cur_c = k1;
  vector<int> days;
  days.reserve(n + 1);
  while (cur_d > 0) {
    if (path[cur_d][cur_c].second > cur_c) {
      days.push_back(cur_d);
    }
    auto q = cur_d;
    cur_d = path[cur_d][cur_c].first;
    cur_c = path[q][cur_c].second;
  }
  out << mmin << '\n' << k1 << ' ' << days.size() << '\n';
  copy(days.rbegin(), days.rend(), ostream_iterator<int>(out, "\n"));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"5 35 40 101 59 63 ", "5 101 101 1 101 1",
                        "5 110 110 70 70 50", "8 56 113 67 86 94 105 87 102"};
  int i = 2;
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
