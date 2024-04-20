#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int mx[1001][1001];
int n, m;
pair<int, int> f(int r, bool isrow) {
  int maxid = -1;
  int maxel = -1;
  for (size_t i = 0; i < n; i++) {
    if (isrow && i == r) {
      continue;
    }
    for (size_t j = 0; j < m; j++) {
      if (!isrow && j == r)
        continue;
      if (maxid == -1 || mx[i][j] > maxel) {
        maxid = isrow ? j : i;
        maxel = mx[i][j];
      }
    }
  }
  int smax = -1;
  for (size_t i = 0; i < n; i++) {
    if ((isrow && i == r) || (!isrow && i == maxid))
      continue;
    for (size_t j = 0; j < m; j++) {
      if ((isrow && j == maxid) || (!isrow && j == r))
        continue;
      if (smax == -1 || mx[i][j] > smax) {
        smax = mx[i][j];
      }
    }
  }
  return {smax, maxid};
}

void solve(istream &in, std::ostream &out) {
  in >> n >> m;
  int max_i = -1, max_j;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      in >> mx[i][j];
      if (max_i == -1 || mx[max_i][max_j] < mx[i][j]) {
        max_i = i;
        max_j = j;
      }
    }
  }
  auto r1 = f(max_i, true);
  auto r2 = f(max_j, false);
  if (r1.first < r2.first) {
    out << max_i + 1 << ' ' << r1.second + 1;
  } else {
    out << r2.second + 1 << ' ' << max_j + 1;
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 2 2 1 2 3 4 ", " 3 4 1 3 5 7 9 11 2 4 6 8 10 12 "};
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
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
