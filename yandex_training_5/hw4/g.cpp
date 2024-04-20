#include <algorithm>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using ll = unsigned long long;

constexpr int MAX_N = 2005;
constexpr int MAX_M = 2005;
int n, m;
int matrix[MAX_N][MAX_M]{0};
int squers[MAX_N][MAX_M]{0};

void solve(istream &in, std::ostream &out) {
  in >> n >> m;
  char c;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      in >> c;
      matrix[i][j] = c == '#';
      squers[i][j] = c == '#';
    }
  }
  for (int i = n - 2; i >= 0; --i) {
    for (int j = m - 2; j >= 0; --j) {
      if (squers[i][j]) {
        squers[i][j] =
            min(squers[i + 1][j], min(squers[i + 1][j + 1], squers[i][j + 1])) +
            1;
      }
    }
  }
  auto check = [&](int k) {
    for (int i = 0; i <= n - k * 3; i++) {
      for (int j = k; j <= m - k * 2; j++) {
        if (squers[i][j] >= k && squers[i + k][j - k] >= k &&
            squers[i + k][j] >= k && squers[i + k][j + k] >= k &&
            squers[i + 2 * k][j] >= k) {
          return true;
        }
      }
    }
    return false;
  };
  int l = 1;
  int r = min(n / 3, m / 3);
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    if (check(m)) {
      l = m;
    } else {
      r = m - 1;
    }
  }
  out << l;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{
      " 9 12 ...##.###... ...##.###... .########... .########### ...######### "
      "...######### ......###... ......###... ......###... ",
      "6 6 .##... .##... ###### ###### .##... .##... "};
  // vector<string> inputs({"6265505"});
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
