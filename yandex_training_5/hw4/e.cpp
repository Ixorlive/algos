#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

using ll = unsigned long long;

// while (l < r) {
//   ll m = l + (r - l + 1) / 2;
//   if (f(m) <= n) {
//     l = m;
//   } else {
//     r = m - 1;
//   }
// }
inline ll f(ll diag) { return diag * (diag + 1) / 2; }

void solve(istream &in, std::ostream &out) {
  ll n;
  in >> n;
  ll l = 1;
  ll r = min(n, (ll)2000000000);
  while (l <= r) {
    ll m = l + (r - l) / 2;
    if (f(m) < n) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  ll left = n - f(l - 1);
  if (l % 2 == 0) {
    out << l - left + 1 << "/" << left;
  } else {
    out << left << "/" << l - left + 1;
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
  vector<string> inputs{"1", "6", "2"};
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
