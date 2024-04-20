#include <bits/stdc++.h>

using namespace std;

std::string sum(const std::string &a, const std::string &b) {
  string result;
  result.reserve(a.size() + b.size());
  int carry = 0;
  string num1 = a, num2 = b;
  reverse(num1.begin(), num1.end());
  reverse(num2.begin(), num2.end());

  while (num1.size() < num2.size()) {
    num1 += '0';
  }
  while (num2.size() < num1.size()) {
    num2 += '0';
  }
  for (size_t i = 0; i < num1.size(); ++i) {
    int digit1 = num1[i] - '0';
    int digit2 = num2[i] - '0';
    int sum = digit1 + digit2 + carry;
    result += (sum % 10) + '0';
    carry = sum / 10;
  }
  if (carry > 0) {
    result += carry + '0';
  }
  reverse(result.begin(), result.end());
  return result;
}
string dp[100][100];
int n, m;
string rec(int i, int j) {
  if (i < 0 || j < 0 || i >= n || j >= m) {
    return "0";
  }
  if (dp[i][j] == "-1") {
    dp[i][j] = sum(sum(rec(i - 2, j - 1), rec(i - 1, j - 2)),
                   sum(rec(i - 2, j + 1), rec(i + 1, j - 2)));
  }
  return dp[i][j];
}

void solve(istream &in, std::ostream &out) {
  in >> n >> m;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      dp[i][j] = "-1";
    }
  }
  dp[0][0] = "1";
  out << rec(n - 1, m - 1);
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"4 4", "2 3"};
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
