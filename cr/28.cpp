#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  size_t dp[1001];
  int p[1001];
  int arr[1001];
  for (int i = 0; i < n; i++) {
    in >> arr[i];
    dp[i] = 1;
    p[i] = -1;
    for (int j = 0; j < i; j++) {
      if (arr[j] < arr[i] && 1 + dp[j] > dp[i]) {
        dp[i] = 1 + dp[j];
        p[i] = j;
      }
    }
  }
  int ans = dp[0];
  int pos = 0;
  for (size_t i = 1; i < n; i++) {
    if (dp[i] > ans) {
      ans = dp[i];
      pos = i;
    }
  }
  int path[1001];
  int q = ans - 1;
  while (pos != -1) {
    path[q--] = arr[pos];
    pos = p[pos];
  }
  copy(path, path + ans, ostream_iterator<int>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"6 3 29 5 5 28 6 ", "10 4 8 2 6 2 10 6 29 58 9 "};
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
