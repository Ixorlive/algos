#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MAXN = 2002;
size_t dp[MAXN][MAXN]{0};

void solve(istream &in, std::ostream &out) {
  string s1, s2;
  in >> s1 >> s2;
  for (size_t i = 1; i <= s1.size(); i++) {
    dp[i][0] = i;
  }
  for (size_t i = 1; i <= s2.size(); i++) {
    dp[0][i] = i;
  }
  for (size_t i = 1; i <= s1.size(); i++) {
    for (size_t j = 1; j <= s2.size(); j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1])) + 1;
      }
    }
  }
  out << dp[s1.size()][s2.size()];
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"ABCDEFGH ACDEXGIH "};
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
