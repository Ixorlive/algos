#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MAXN = 100 + 10;

int n, m;

int mx[MAXN][MAXN]{0};
int wx[MAXN][MAXN]{0};

size_t holls = 0;

bool dfs(int i, int j, int init) {
  if (wx[i][j] > 0)
    return wx[i][j] == 3;
  if (mx[i - 1][j] < mx[i][j] || mx[i][j - 1] < mx[i][j] ||
      mx[i][j + 1] < mx[i][j] || mx[i + 1][j] < mx[i][j]) {
    wx[i][j] = 3;
    return true;
  }

  wx[i][j] = init;

  if ((mx[i + 1][j] == mx[i][j] && dfs(i + 1, j, 2)) ||
      (mx[i][j + 1] == mx[i][j] && dfs(i, j + 1, 2)) ||
      (mx[i - 1][j] == mx[i][j] && dfs(i - 1, j, 2)) ||
      (mx[i][j - 1] == mx[i][j] && dfs(i, j - 1, 2))) {
    wx[i][j] = 2;
    return true;
  }
  if (init == 1)
    ++holls;
  return false;
}

void solve(istream &in, std::ostream &out) {
  in >> n >> m;
  for (size_t i = 0; i <= m + 1; i++) {
    mx[0][i] = 1e9;
    mx[n + 1][i] = 1e9;
  }
  for (size_t i = 0; i <= n + 1; i++) {
    mx[i][0] = 1e9;
    mx[i][m + 1] = 1e9;
  }
  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= m; j++) {
      in >> mx[i][j];
    }
  }
  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= m; j++) {
      dfs(i, j, 1);
    }
  }
  out << holls;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 4 4 1 2 4 1 2 4 4 4 1 4 3 2 1 2 3 2 ",
                        "4 4 1 2 3 4 1 1 2 3 4 1 0 4 4 4 4 4"};
  int i = 1;
  if (i == -1) {
    for (int i = 0; i < inputs.size(); ++i) {
      istringstream in(inputs[i]);
      ostringstream out;
      solve(in, out);
      cout << "+==== Test #" << i + 1 << " ====+\n";
      cout << out.str();
      cout << "\n";
    }
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
