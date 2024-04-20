#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr size_t SECS = 9 * 3600;
constexpr size_t BREAKTIME = 13 * 3600 - SECS;

size_t tvs[SECS + 100]{0};
size_t dp[SECS + 100]{0};

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int h, m, s, T;
  char ch;
  for (size_t i = 0; i < n; i++) {
    in >> h >> ch >> m >> ch >> s >> T;
    tvs[h * 3600 + m * 60 + s - SECS] = T;
  }
  int curtv;
  size_t mmax = 0;
  for (size_t i = 0; i < SECS; i++) {
    if (tvs[i] != 0) {
      curtv = tvs[i];
    }
    mmax = max(dp[i], mmax);
    if ((i >= BREAKTIME && i < BREAKTIME + 3600) ||
        (i + curtv > BREAKTIME && i < BREAKTIME) || i + curtv > SECS) {
      continue;
    }
    dp[i + curtv] = max(dp[i + curtv], mmax + 1);
  }
  mmax = max(mmax, dp[SECS]);
  out << mmax;
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
      "2 09:00:00 3600 14:00:00 3600 ",
      "4 09:00:00 1800 12:59:31 10 13:45:23 1800 15:00:00 3600 "};
  int i = 0;
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
