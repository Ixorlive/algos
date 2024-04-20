#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

using ll = unsigned long long;

inline ll f(ll k) {
  return (k * (k + 1) * (k + 2)) / 6 + (k * (k + 1) / 2) - 1;
}

void solve(istream &in, std::ostream &out) {
  ll n;
  in >> n;
  ll l = 0;
  ll m = 2000000;
  ll r = min(m, n);
  while (l < r) {
    ll m = l + (r - l + 1) / 2;
    if (f(m) <= n) {
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
  // vector<string> inputs{"7", "6265505"};
  vector<string> inputs({"6265505"});
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
