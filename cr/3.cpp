#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

size_t dp[101][101]{0};
int p[101][101]{0};
size_t a[101][101]{0};

void solve(istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      in >> a[i][j];
    }
  }
  dp[0][0] = a[0][0];
  p[0][0] = -1;
  for (size_t i = 1; i < m; i++) {
    dp[0][i] = dp[0][i - 1] + a[0][i];
    p[0][i] = 1;
  }
  for (size_t i = 1; i < n; i++) {
    dp[i][0] = dp[i - 1][0] + a[i][0];
    p[i][0] = 2;
  }
  for (size_t i = 1; i < n; i++) {
    for (size_t j = 1; j < m; j++) {
      if (dp[i - 1][j] > dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j] + a[i][j];
        p[i][j] = 2;
      } else {
        dp[i][j] = dp[i][j - 1] + a[i][j];
        p[i][j] = 1;
      }
    }
  }
  int pos = p[n - 1][m - 1];
  int i = n - 1;
  int j = m - 1;
  char respath[101 * 2 + 10];
  int q = n + m - 3;
  while (pos != -1) {
    if (pos == 2) {
      respath[q] = 'D';
      --i;
    } else {
      respath[q] = 'R';
      --j;
    }
    pos = p[i][j];
    --q;
  }
  out << dp[n - 1][m - 1] << '\n';
  copy(respath, respath + n + m - 2, ostream_iterator<char>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{
      "5 5 9 9 9 9 9 3 0 0 0 0 9 9 9 9 9 6 6 6 6 8 9 9 9 9 9 ",
      "3 4 5 9 4 3 3 1 6 9 8 6 8 12 ", "1 1 1"};
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
