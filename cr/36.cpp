#include <bits/stdc++.h>

using namespace std;

int c[102];
int n;
long long d[102][102];

long long dp(int l, int r) {
  if (l >= r) {
    return 0;
  }
  if (d[l][r] != -1) {
    return d[l][r];
  }
  if (l == r - 1) {
    d[l][r] = 0;
  } else {
    long long minr = -1;
    for (int i = l + 1; i <= r - 1; i++) {
      auto v = dp(l, i) + dp(i, r);
      if (minr == -1 || minr > v) {
        minr = v;
      }
    }
    d[l][r] = minr + (c[r] - c[l]);
  }
  return d[l][r];
}

void solve(istream &in, std::ostream &out) {
  size_t len;
  in >> len >> n;
  c[0] = 0;
  c[n + 1] = len;
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= n + 1; ++j) {
      d[i][j] = -1;
    }
  }
  for (size_t i = 1; i <= n; i++) {
    in >> c[i];
  }
  out << dp(0, n + 1);
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"10 3 2 4 7 ", "100 3 15 50 75 "};
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
