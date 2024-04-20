#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 50;

int a[MAXN][MAXN];
long long pref[MAXN + 10][MAXN + 10]{0};

void solve(istream &in, std::ostream &out) {
  int n, m, k;
  in >> n >> m >> k;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      in >> a[i][j];
    }
  }
  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= m; j++) {
      pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] +
                   a[i - 1][j - 1];
    }
  }
  int i1, j1, i2, j2;
  for (size_t i = 0; i < k; i++) {
    in >> i1 >> j1 >> i2 >> j2;
    out << pref[i2][j2] - pref[i2][j1 - 1] - pref[i1 - 1][j2] +
               pref[i1 - 1][j1 - 1]
        << '\n';
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"3 3 2 1 2 3 4 5 6 7 8 9 2 2 3 3 1 1 2 3 "};
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
